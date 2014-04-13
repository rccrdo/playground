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

#ifndef pg_rigidbody_vector_h
#define pg_rigidbody_vector_h

#include "la.h"
#include "pg_array_container.h"
#include "pg_rigidbody.h"
#include "pg_sphere.h"
#include "pg_plane.h"
#include "pg_debug.h"
#include "pg_config.h"

/* select the size of slots, aligning to sizeof(las) */
#define PG_RIGIDBODY_VECTOR__SLOT_SIZE sizeof(pg_rigidbody)
#if sizeof(pg_sphere) > sizeof(pg_rigidbody) 
#define PG_RIGIDBODY_VECTOR__SLOT_SIZE (sizeof(pg_sphere)%sizeof(las) +1)*sizeof(las)
#endif
#if sizeof(pg_plane) > sizeof(pg_sphere) 
#define PG_RIGIDBODY_VECTOR__SLOT_SIZE (sizeof(pg_plane)%sizeof(las) +1)*sizeof(las)
#endif


typedef struct pg_rigidbody_vector {
	/* private */
	struct pg_array_container ac;
} pg_rigidbody_vector;

/**
 * Inits a pg_rigidbody_vector
 * @v pg_rigidbody_vector to be used
 */
__pg_inline__ void pg_rigidbody_vector_init(struct pg_rigidbody_vector *v);

/**
 * Deinits a pg_rigidbody_vector
 * @v pg_rigidbody_vector to be used
 */
__pg_inline__ void pg_rigidbody_vector_deinit(struct pg_rigidbody_vector *v);

/**
 * Returns the element at a given position
 * @v pg_rigidbody_vector to be used
 * @at index of the elemnt
 *
 * returns pointer to the pg_rigidbody struct in the vector at the given index
 */
__pg_inline__ pg_rigidbody_vector *v
pg_rigidbody_vector_get_ptr_at(struct pg_rigidbody_vector *v, unsigned int at);

/**
 * Clears the vector
 * @v pg_rigidbody_vector to be used
 */
__pg_inline__ void pg_rigidbody_vector_clear(struct pg_rigidbody_vector *v);

/**
 * Appends one uninitialized pg_rigidbody to the vector
 * @v pg_rigidbody_vector to be used
 *
 * returns pointer to the added pg_rigidbody struct
 */
__pg_inline__ pg_rigidbody_vector *v
pg_rigidbody_vector_append_rigidbody_uninitialized(struct pg_rigidbody_vector *v);

#include "pg_rigidbody_vector-impl.h"
                                 
#endif /* pg_rigidbody_vector_h */

