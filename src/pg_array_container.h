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

#ifndef pg_array_container_h
#define pg_array_container_h

#include <stdio.h>

#include "pg_memblock.h"
#include "pg_debug.h"
#include "pg_config.h"


/* protected api */

/* minimum number of slots reserved in a pg_array_container
 * ! must be a power of two  */
#define PG_ARRAY_CONTAINER_MIN_RESERVED_SLOTS (unsigned int)32


struct pg_array_container {
	/* private */
	struct pg_memblock mblock;
	unsigned int size;	 /* in slots                 */
	unsigned int reserved; /* reserved memory in slots */
};


/**
 * Inits a pg_array_container
 * @ac pg_array_container to be used
 * @slot_size slots size (in bytes)
 *
 * return 0 on success and !0 otherwise
 */
__pg_inline__ int pg_array_container_init(struct pg_array_container *ac, unsigned int slot_size);

/**
 * Deinits a pg_array_container
 * @ac pg_array_container to be used
 */
__pg_inline__ void pg_array_container_deinit(struct pg_array_container *ac);

/**
 * Clears the container
 */
__pg_inline__ void pg_array_container_clear(struct pg_array_container *ac, unsigned int slot_size);


/**
 * Common helper for growing pg_array_container implementors
 * @ac pg_array_container to be used
 */
__pg_inline__ void pg_array_container_grow_once(struct pg_array_container *ac);


/**
 * Reserves memory for the given number of slots
 * @ac pg_array_container to be used
 * @slot_size size of a slot (in bytes)
 * @num_slots requested new number of slots
 *
 * The number of slots reserved will be the nearest higher power of two for num_slots
 */
__pg_inline__ void pg_array_container_reserve(struct pg_array_container *ac,
					      unsigned int slot_size,
					      unsigned int num_slots);


/**
 * Grows the container when its size equals its reserved size
 */
__pg_inline__ void pg_array_container_check_size_and_grow(struct pg_array_container *ac);




__pg_inline__ int pg_array_container_init(struct pg_array_container *ac, unsigned int slot_size) {
	int ret;
	pg_assert(ac && slot_size);
	ac->reserved = PG_ARRAY_CONTAINER_MIN_RESERVED_SLOTS;
	ac->size = 0;
	ret = pg_memblock_init(&ac->mblock, slot_size*PG_ARRAY_CONTAINER_MIN_RESERVED_SLOTS);
	return ret;
}


__pg_inline__ void pg_array_container_deinit(struct pg_array_container *ac) {
	pg_assert(ac);
	pg_memblock_deinit(&ac->mblock);
}


__pg_inline__ void pg_array_container_clear(struct pg_array_container *ac, unsigned int slot_size) {
	pg_assert(ac && slot_size);
	ac->reserved = PG_ARRAY_CONTAINER_MIN_RESERVED_SLOTS;
	ac->size = 0;
	pg_memblock_set_size(&ac->mblock, slot_size*PG_ARRAY_CONTAINER_MIN_RESERVED_SLOTS);

}

__pg_inline__ void pg_array_container_grow_once(struct pg_array_container *ac)
{
	pg_assert(ac);
	/* always grow by a factor of 2 */
	pg_memblock_set_size(&ac->mblock, ac->mblock.size*2);
	ac->reserved *= 2;  
}


__pg_inline__ void pg_array_container_reserve(struct pg_array_container *ac,
                                              unsigned int slot_size,
                                              unsigned int num_slots)
{
	pg_assert(ac && slot_size && num_slots);

	/* respect lower threshold */
	if (num_slots < PG_ARRAY_CONTAINER_MIN_RESERVED_SLOTS)
		num_slots = PG_ARRAY_CONTAINER_MIN_RESERVED_SLOTS;
	else {
		/* compute the next highest power of 2 for num_slots */
		num_slots--;
		num_slots |= num_slots >> 1;
		num_slots |= num_slots >> 2;
		num_slots |= num_slots >> 4;
		num_slots |= num_slots >> 8;
		num_slots |= num_slots >> 16;
		num_slots++;
	}

	if (ac->reserved != num_slots) {
		pg_memblock_set_size(&ac->mblock, num_slots*slot_size);
		ac->reserved = num_slots;
		/* avoid weird values for size */
		if (ac->size > ac->reserved)
			ac->size = ac->reserved;
	}
}

__pg_inline__ void pg_array_container_check_size_and_grow(struct pg_array_container *ac) {
	pg_assert(ac);
	if (ac->reserved == ac->size) 
		pg_array_container_grow_once(ac);
}

#endif /* pg_array_container_h */

