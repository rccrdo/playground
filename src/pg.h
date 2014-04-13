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

#ifndef playground_h
#define playground_h

#include <stdlib.h>
#include "pg_rigidbody.h"
#include "pg_vector_ptrs.h"
#include "pg_debug.h"


typedef struct playground {
	/* private */
	pg_vector_ptrs rigid_bodies;  /* rigid bodies in the playground */
} playground;


/**
 * creates and inits a new playground
 *
 * returns the ptr to the new playground or NULL on failure.
 */
playground *playground_new(void);

/**
 * deinits and frees a playground
 * @pg ptr to the playground object
 */
void playground_free(playground *pg);

/**
 * step the playground !
 * @time_delta time duration of the step
 */
void playground_step(playground *pg, las time_delta);

/**
 * add a body to the playground
 * @pg playground to be used
 * @body to be added
 */
void playground_add_body(playground *pg, pg_rigidbody *body);

#endif /* playground_h */

