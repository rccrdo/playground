/*
 * Copyright (c) 2008 Riccardo Lucchese, riccardo.lucchese at gmail.com
 * 
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 
 *    1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 
 *    2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 
 *    3. This notice may not be removed or altered from any source
 *    distribution.
 */

#ifndef pg_memblock_h
#define pg_memblock_h

#include <stdlib.h>
#include "pg_config.h"
#include "pg_debug.h"

struct pg_memblock {
	/* private */
	void* mem;
	unsigned int size;	/* in bytes */
};


/**
 * Inits a pg_memblock allocating the given amount of bytes
 * @mb ptr to the pg_memblock struct to be inited
 * @s amount of bytes to be reserved
 *
 * return 0 on success and !0 otherwise
 */
__pg_inline__ int pg_memblock_init(struct pg_memblock *mb, unsigned int s);


/**
 * `deinits' a pg_memblock and frees his contents
 */
__pg_inline__ void pg_memblock_deinit(struct pg_memblock *mb);


/**
 * Reallocs the internal buffer to the given number of bytes
 * @mb pg_memblock to be used
 * @r new size in bytes
 */
__pg_inline__ void pg_memblock_set_size(struct pg_memblock *mb, unsigned int r);


/**
 * Copies the passed buffer to the pg_memblock
 * @mb pg_memblock to be used
 * @buf ptr to the memory chunk to copy
 * @len number of bytes to copy
 *
 * Implmentation takes care of calling pg_memblock_set_size
 * when the pg_memblock size is to little. 
 */
__pg_inline__ void pg_memblock_assign(struct pg_memblock *mb,
                                      const void* buf,
                                      unsigned int len);


/**
 * Memsets contents of pg_memblock to a given value
 * @mb pg_memblock to be used
 * @c value to use for memset
 */
__pg_inline__ void pg_memblock_set (struct pg_memblock *mb, unsigned char c);


/**
 * Clones two memblocks
 * @dest destination block
 * @src source block
 */
__pg_inline__ void pg_memblock_clone(struct pg_memblock *dest,
                                     struct pg_memblock *src);


__pg_inline__ int pg_memblock_init(struct pg_memblock *mb, unsigned int s) {
	pg_assert(mb && s);
	mb->size = s;
	mb->mem = malloc(s);
	return mb->mem == NULL;
}

__pg_inline__ void pg_memblock_deinit(struct pg_memblock *mb) {
	pg_assert(mb);
	free(mb->mem);
}

__pg_inline__ void pg_memblock_set_size(struct pg_memblock *mb,
					unsigned int r) {
	pg_assert(mb && r);
	mb->size = r;
	mb->mem = realloc(mb->mem, mb->size);
	if (!mb->mem) {
		printf("warning pg_memblock_set_size, realloc failed\n");
		pg_assert(0);
	}
}


__pg_inline__ void pg_memblock_assign(struct pg_memblock *mb,
                                      const void* buf,
                                      unsigned int len) {
	pg_assert(mb && buf && len);
	/* check if realloc is necessary */
	if (len > mb->size)
		pg_memblock_set_size(mb, len);
	memcpy(mb->mem,buf,len);
}


__pg_inline__ void pg_memblock_set(struct pg_memblock *mb, unsigned char c) {
	pg_assert(mb);
	memset(mb->mem,c,mb->size);
}

__pg_inline__ void pg_memblock_clone(struct pg_memblock *dest,
                                     struct pg_memblock *src) {
	pg_assert(dest && src);
	pg_memblock_deinit(dest);
	pg_memblock_init(dest, src->size);
	pg_memblock_assign(dest, src->mem, src->size);
}

#endif /* pg_memblock_h */

