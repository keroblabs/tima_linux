
void * memcpy_be( void *v_dst, const void *v_src, long c )
{
	const char *src = ( const char * )v_src;
	char *dst = ( char * )v_dst;

    src += ( c - 1 );

	/* Simple, byte oriented memcpy. */
	while (c--)
		*dst++ = *src--;

    return v_dst;
}
