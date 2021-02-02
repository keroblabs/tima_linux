#include "t_lzw.h"

////////////////////////////////////////////////////////////////////////////////////////

#define DICT_SIZE			512 // (1 << 11)
#define NODE_NULL			(-1)
#define LZW_BUFFER_SIZE		256

////////////////////////////////////////////////////////////////////////////////////////

typedef unsigned int code_t;

////////////////////////////////////////////////////////////////////////////////////////

typedef struct _bitbuffer
{
    unsigned buf;
    unsigned n;

} bitbuffer_t;

// LZW node, represents a string
typedef struct _node
{
    code_t  prev;   // prefix code
    code_t  first;  // firts child code
    code_t  next;   // next child code
    char    ch;             // last symbol

} node_t;

// LZW context
typedef struct _lzw
{
    node_t        dict[DICT_SIZE];  // code dictionary
    unsigned      max;                              // maximal code
    unsigned      codesize;                 // number of bits in code
    bitbuffer_t   bb;                               // bit-buffer struct
    unsigned char *stream;                  // pointer to the buffer object
	unsigned char *output;					// pointer to output buffer
	unsigned	  s_size;					// size of the stream
	unsigned	  s_pointer;				// stream current position
	unsigned	  o_size;
    unsigned      lzwn;                             // buffer byte counter
    unsigned      lzwm;                             // buffer size (decoder only)
    unsigned char buff[LZW_BUFFER_SIZE];                // stream buffer, adjust its size if you need

} lzw_t;

static unsigned char buff[DICT_SIZE];

// global object
static lzw_t lzw;

////////////////////////////////////////////////////////////////////////////////////////

static void lzw_flushbuf(lzw_t *ctx)
{
	memcpy( &ctx->output[ctx->o_size], ctx->buff, ctx->lzwn );
	ctx->o_size += ctx->lzwn;
}

static void lzw_writebuffer( lzw_t *ctx, unsigned char * buff, int size )
{
	memcpy( &ctx->output[ctx->o_size], buff, size );
	ctx->o_size += size;
}

static void lzw_writebyte(lzw_t *ctx, const unsigned char b)
{
    ctx->buff[ctx->lzwn++] = b;

	if( ctx->lzwn >= LZW_BUFFER_SIZE )
	{
		memcpy( &ctx->output[ctx->o_size], ctx->buff, LZW_BUFFER_SIZE );
		ctx->o_size += LZW_BUFFER_SIZE;
        ctx->lzwn = 0;
	}
}

static unsigned char lzw_readbyte(lzw_t *ctx)
{
	int i;

	if (ctx->lzwn == ctx->lzwm)
	{
		for( i = 0; i < LZW_BUFFER_SIZE; i++ )
		{
			if( ctx->s_pointer >= ctx->s_size ) break;
			ctx->buff[i] = ctx->stream[ctx->s_pointer];

			ctx->s_pointer++;
		}

		ctx->lzwm = i;
		ctx->lzwn = 0;
	}

	return ctx->buff[ctx->lzwn++];
}

static int lzw_getc(lzw_t *ctx)
{
	if( ctx->s_pointer >= ctx->s_size ) 
	{
		return EOF;
	}
	return ctx->stream[ctx->s_pointer++];
}

static void lzw_writebits(lzw_t *ctx, unsigned bits, unsigned nbits)
{
    // shift old bits to the left, add new to the right
    ctx->bb.buf = (ctx->bb.buf << nbits) | (bits & ((1 << nbits)-1));

    nbits += ctx->bb.n;

    // flush whole bytes
    while (nbits >= 8) 
	{
        unsigned char b;

        nbits -= 8;
        b = ctx->bb.buf >> nbits;

        lzw_writebyte(ctx, b);
    }

    ctx->bb.n = nbits;
}

static unsigned lzw_readbits(lzw_t *ctx, unsigned nbits)
{
    unsigned bits;

    // read bytes
    while (ctx->bb.n < nbits) 
	{
        unsigned char b = lzw_readbyte(ctx);

        // shift old bits to the left, add new to the right
        ctx->bb.buf = (ctx->bb.buf << 8) | b;
        ctx->bb.n += 8;
    }

    ctx->bb.n -= nbits;
    bits = (ctx->bb.buf >> ctx->bb.n) & ((1 << nbits)-1);

    return bits;
}

static void lzw_flushbits(lzw_t *ctx)
{
    if (ctx->bb.n & 7)
            lzw_writebits(ctx, 0, 8-(ctx->bb.n & 3));
}

static void lzw_init(lzw_t *ctx, unsigned char *stream, int size, unsigned char * output)
{
    unsigned i;

    memset(ctx, 0, sizeof(*ctx));
        
    for (i = 0; i < 256; i++)
    {
        ctx->dict[i].prev = NODE_NULL;
        ctx->dict[i].first = NODE_NULL;
        ctx->dict[i].next = NODE_NULL;
        ctx->dict[i].ch = i;
    }

    ctx->max = i-1;
    ctx->codesize = 8;

	ctx->output = output;
    ctx->stream = stream;
	ctx->s_size = size;
	ctx->s_pointer = 0;
	ctx->o_size = 0;
}

static code_t lzw_find_str(lzw_t *ctx, code_t code, char c)
{
    code_t nc;

    for (nc = ctx->dict[code].first; nc != NODE_NULL; nc = ctx->dict[nc].next)
    {
        if (code == ctx->dict[nc].prev && c == ctx->dict[nc].ch)
                return nc;
    }

    return NODE_NULL;
}

static unsigned lzw_get_str(lzw_t *ctx, code_t code, unsigned char buff[], unsigned size)
{
    unsigned i = size;

    while (code != NODE_NULL && i)
    {
        buff[--i] = ctx->dict[code].ch;
        code = ctx->dict[code].prev;
    }

    return size - i;
}

static code_t lzw_add_str(lzw_t *ctx, code_t code, char c)
{
    ctx->max++;

    if (ctx->max >= DICT_SIZE)
        return NODE_NULL;
        
    ctx->dict[ctx->max].prev = code;
    ctx->dict[ctx->max].first = NODE_NULL;
    ctx->dict[ctx->max].next = ctx->dict[code].first;
    ctx->dict[code].first = ctx->max;
    ctx->dict[ctx->max].ch = c;

    return ctx->max;
}

static void lzw_write(lzw_t *ctx, code_t code)
{
    // increase the code size (number of bits) if needed
    if (ctx->max == (1 << ctx->codesize))
        ctx->codesize++;

    lzw_writebits(ctx, code, ctx->codesize);
}

static code_t lzw_read(lzw_t *ctx)
{
    // increase the code size (number of bits) if needed
    if (ctx->max+1 == (1 << ctx->codesize))
        ctx->codesize++;

    return lzw_readbits(ctx, ctx->codesize);
}

int tzip_encode(unsigned char * input, int input_size, unsigned char * output)
{
	lzw_t *ctx = &lzw;
    code_t   code;
    unsigned isize = 0;
    unsigned strlen = 0;
    int      c;

	if( input_size > INPUT_BUFFER ) return LZW_TOO_BIG;

    lzw_init(ctx, input, input_size, output);

    if ((c = lzw_getc(ctx)) == EOF) return LZW_EOF;

    code = c;
    isize++;
    strlen++;

    while ((c = lzw_getc(ctx)) != EOF)
    {
        code_t nc;

        isize++;

        nc = lzw_find_str(ctx, code, c);

        if (nc == NODE_NULL)
        {
            code_t tmp;

            // the string was not found - write <prefix>
            lzw_write(ctx, code);

            // add <prefix>+<current symbol> to the dictionary
            tmp = lzw_add_str(ctx, code, c);

            if (tmp == NODE_NULL) return -1;

            code = c;
            strlen = 1;
        }
        else
        {
            code = nc;
            strlen++;
        }
    }
    // write last code
    lzw_write(ctx, code);
    lzw_flushbits(ctx);
    lzw_flushbuf(ctx);

    return ctx->o_size;
}

int tzip_decode(unsigned char * input, int input_size, unsigned char * output)
{
	lzw_t *ctx = &lzw;
    unsigned      isize = 0;
    code_t        code;
    unsigned char c;

    lzw_init(ctx, input, input_size, output);

    c = code = lzw_readbits(ctx, ctx->codesize++);
    // write symbol into the output stream
	lzw_writebuffer( ctx, &c, 1 );

    while( 1 )
    {
        unsigned      strlen;
        code_t        nc;

        nc = lzw_read(ctx);

        // check input strean for EOF (lzwm == 0)
        if (!ctx->lzwm) break;

        // unknown code
        if (nc > ctx->max)
        {
            if (nc-1 == ctx->max) 
			{
                if (lzw_add_str(ctx, code, c) == NODE_NULL) return LZW_DICT_FULL;
                code = NODE_NULL;
            }
            else return LZW_DICT_ERROR;
        }

        // get string for the new code from dictionary
        strlen = lzw_get_str(ctx, nc, buff, sizeof(buff));
        // remember the first sybmol of this string
        c = buff[sizeof(buff) - strlen];
        // write the string into the output stream
		lzw_writebuffer(ctx, buff+(sizeof(buff) - strlen), strlen);

        if (code != NODE_NULL)
        {
            // add <prev code str>+<first str symbol> to the dictionary
            if (lzw_add_str(ctx, code, c) == NODE_NULL) return -1;
        }

        code = nc;
        isize++;
    }

    return ctx->o_size;
}
