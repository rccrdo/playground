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

#ifndef pg_vector_ptrs_h
#define pg_vector_ptrs_h

#include "pg_array_container.h"
#include "pg_debug.h"
#include "pg_config.h"


typedef struct pg_vector_ptrs {
	/* private */
	struct pg_array_container ac;
} pg_vector_ptrs;

/**
 * Inits a pg_vector_ptrs
 * @v pg_vector_ptrs to be used
 *
 * return 0 on success and !0 otherwise
 */
__pg_inline__ int pg_vector_ptrs_init(struct pg_vector_ptrs *v);

/**
 * Deinits a pg_vector_ptrs
 * @v pg_vector_ptrs to be used
 */
__pg_inline__ void pg_vector_ptrs_deinit(struct pg_vector_ptrs *v);

/**
 * Returns the element at a given position
 * @v pg_vector_ptrs to be used
 * @at index of the elemnt
 */
__pg_inline__ void* pg_vector_ptrs_at(struct pg_vector_ptrs *v,
                                      unsigned int at);
/**
 * Sets the element at a given position
 * @v pg_vector_ptrs to be used
 * @at index of the elemnt
 * @value new value
 */
__pg_inline__ void pg_vector_ptrs_set(struct pg_vector_ptrs *v,
                                      unsigned int at,
                                      void* value);


/**
 * Clears the vector
 * @v pg_vector_ptrs to be used
 */
__pg_inline__ void pg_vector_ptrs_clear(struct pg_vector_ptrs *v);

/**
 * Pushes a new element at the back of the vector
 * @v pg_vector_ptrs to be used
 * @value new value
 */
__pg_inline__ void pg_vector_ptrs_push_back(struct pg_vector_ptrs *v,
                                            void* value);

/**
 * Reserves memory for the given number of ptrss
 * @v pg_vector_ptrs to be used
 * @r number of ptrss
 */
__pg_inline__ void pg_vector_ptrs_reserve(struct pg_vector_ptrs *v,
                                          unsigned int num_slots);

/**
 * Returns the number of reserved slots
 * @v pg_vector_ptrs to be used
 */
__pg_inline__ unsigned int pg_vector_ptrs_reserved(struct pg_vector_ptrs *v);

/**
 * Returns the size of the vector
 * @v pg_vector_ptrs to be used
 */
__pg_inline__ unsigned int pg_vector_ptrs_size(struct pg_vector_ptrs *v);


/**
 * Clones two vectors
 * @dest destination vector
 * @src source vector
 */
__pg_inline__ void pg_vector_ptrs_clone(struct pg_vector_ptrs *dest,
                                        struct pg_vector_ptrs *src );


__pg_inline__ int pg_vector_ptrs_init(struct pg_vector_ptrs *v) {
	int ret;
	pg_assert(v);
	ret = pg_array_container_init(&v->ac, sizeof(void*));
	return ret;
}

__pg_inline__ void pg_vector_ptrs_deinit(struct pg_vector_ptrs *v) {
	pg_assert(v);
	pg_array_container_deinit(&v->ac);
}


__pg_inline__ void* pg_vector_ptrs_at(struct pg_vector_ptrs *v,
                                      unsigned int at) {
	pg_assert(v && (at < v->ac.size));
	return ((void**) v->ac.mblock.mem)[at];
}


__pg_inline__ void pg_vector_ptrs_set(struct pg_vector_ptrs *v,
                                      unsigned int at,
                                      void* value) {
	pg_assert(v && (at < v->ac.size));
	((void**) v->ac.mblock.mem)[at] = value;
}


__pg_inline__ void pg_vector_ptrs_clear(struct pg_vector_ptrs *v) {
	pg_assert(v);
	pg_array_container_clear(&v->ac, sizeof(void*));
}


__pg_inline__ void pg_vector_ptrs_push_back(struct pg_vector_ptrs *v,
                                            void* value) {
	pg_assert(v);
	/* check for the need of more memory */
	pg_array_container_check_size_and_grow(&v->ac);
	((void**)v->ac.mblock.mem)[v->ac.size] = value;
	v->ac.size ++;
}


__pg_inline__ void pg_vector_ptrs_reserve(struct pg_vector_ptrs *v,
                                          unsigned int num_slots) {
	pg_assert(v && num_slots);
	pg_array_container_reserve(&v->ac, sizeof(void*), num_slots);
}


__pg_inline__ unsigned int pg_vector_ptrs_reserved(struct pg_vector_ptrs *v) {
	pg_assert(v);
	return v->ac.reserved;
}

__pg_inline__ unsigned int pg_vector_ptrs_size(struct pg_vector_ptrs *v) {
	pg_assert(v);
	return v->ac.size;
}

__pg_inline__ void pg_vector_ptrs_clone(struct pg_vector_ptrs *dest,
                                        struct pg_vector_ptrs *src) {
	unsigned int i;
	pg_assert(dest && src);
	pg_vector_ptrs_clear(dest);
  
	for (i=0; i< pg_vector_ptrs_size(src); i++)
		pg_vector_ptrs_push_back(dest, pg_vector_ptrs_at(src,i));
}
                                 
#endif /* pg_vector_ptrs_h */

