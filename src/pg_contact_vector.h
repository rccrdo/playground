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

#ifndef pg_contact_vector_h
#define pg_contact_vector_h

#include "pg_array_container.h"
#include "pg_contact.h"
#include "pg_debug.h"
#include "pg_config.h"


typedef struct pg_contact_vector {
	/* private */
	struct pg_array_container ac;
} pg_contact_vector;

/**
 * Inits a pg_contact_vector
 * @v pg_contact_vector to be used
 */
__pg_inline__ void pg_contact_vector_init(struct pg_contact_vector *v);

/**
 * Deinits a pg_contact_vector
 * @v pg_contact_vector to be used
 */
__pg_inline__ void pg_contact_vector_deinit(struct pg_contact_vector *v);

/**
 * Returns the element at a given position
 * @v pg_contact_vector to be used
 * @at index of the elemnt
 *
 * returns pointer to the pg_contact struct in the vector at the given index
 */
__pg_inline__ pg_contact_vector *v
pg_contact_vector_get_ptr_at(struct pg_contact_vector *v, unsigned int at);

/**
 * Clears the vector
 * @v pg_contact_vector to be used
 */
__pg_inline__ void pg_contact_vector_clear(struct pg_contact_vector *v);

/**
 * Appends one uninitialized pg_contact to the vector
 * @v pg_contact_vector to be used
 *
 * returns pointer to the added pg_contact struct
 */
__pg_inline__ pg_contact_vector *v
pg_contact_vector_append_contact_uninitialized(struct pg_contact_vector *v);

#include "pg_contact_vector-impl.h"
                                 
#endif /* pg_contact_vector_h */

