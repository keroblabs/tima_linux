/*
 * Copyright (c) 2015 Grzegorz Kostka (kostka.grzegorz@gmail.com)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * - The name of the author may not be used to endorse or promote products
 *   derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include "ext4_config.h"
#include "ext4_blockdev.h"
#include "ext4_errno.h"

#include "types.h"
#include "system.h"

#define FILENAME_IMAGE      "/Users/marciocherobim/Projects/GIT/timaos_v41/Applications/instruments/image_dsk/image.bin"
#define IMAGE_OFFSET		(0x00000)

/**********************BLOCKDEV INTERFACE**************************************/
static int blockdev_open(struct ext4_blockdev *bdev);
static int blockdev_bread(struct ext4_blockdev *bdev, void *buf, uint64_t blk_id,
			 uint32_t blk_cnt);
static int blockdev_bwrite(struct ext4_blockdev *bdev, const void *buf,
			  uint64_t blk_id, uint32_t blk_cnt);
static int blockdev_close(struct ext4_blockdev *bdev);

/******************************************************************************/
EXT4_BLOCKDEV_STATIC_INSTANCE(blockdev, 512, (1024*1024), blockdev_open,
			      blockdev_bread, blockdev_bwrite, blockdev_close);

/******************************************************************************/
static int blockdev_open(struct ext4_blockdev *bdev)
{
    
	return EOK;
}

/******************************************************************************/

static int blockdev_bread(struct ext4_blockdev *bdev, void *buf, uint64_t blk_id,
			 uint32_t blk_cnt)
{
    FILE * fp = NULL;
    uint64_t addr;
    uint64_t size;
    
    size = blk_cnt*512;
    addr = blk_id*512;
    
    addr += IMAGE_OFFSET;
    fp = fopen( FILENAME_IMAGE, "r+b" );
    if( fp == NULL ) return MAL_FAIL;
    
    fseek( fp, addr, SEEK_SET );
    fread( buf, size, 1, fp );
    fclose( fp );
    return EOK;
}


/******************************************************************************/
static int blockdev_bwrite(struct ext4_blockdev *bdev, const void *buf,
			  uint64_t blk_id, uint32_t blk_cnt)
{
    FILE * fp = NULL;
    uint64_t addr;
    uint64_t size;
    
    size = blk_cnt*512;
    addr = blk_id*512;
    
    addr += IMAGE_OFFSET;
    fp = fopen( FILENAME_IMAGE, "r+b" );
    if( fp == NULL ) return MAL_FAIL;
    
    fseek( fp, addr, SEEK_SET );
    fwrite( buf, size, 1, fp );
    fclose( fp );
	return EOK;
}
/******************************************************************************/
static int blockdev_close(struct ext4_blockdev *bdev)
{
	/*blockdev_close: skeleton*/
	return EOK;
}

/******************************************************************************/
struct ext4_blockdev *ext4_blockdev_get(void)
{
	return &blockdev;
}
/******************************************************************************/

