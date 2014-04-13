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

#include "playground.h"

playground *playground_new(void) {
	int ret;
	playground *pg;
  
	pg = malloc(sizeof(playground));
	if (pg == NULL)
		return NULL;

	ret = pg_vector_ptrs_init(&pg->rigid_bodies);
	if (ret) {
		free(pg);
		return NULL;
	}
	return pg;
}


void playground_free(playground *pg) {
	pg_assert(pg);
	pg_vector_ptrs_deinit(&pg->rigid_bodies);
	free(pg);
}


void playground_step(playground *pg, las time_delta) {
	unsigned int i;
	unsigned int num_particles;

	pg_assert(pg);

	/* update forces */

	/* collide bodies */

	/* integrate bodies */
	num_particles = pg_vector_ptrs_size(&pg->rigid_bodies);
	for (i=0; i < num_particles; i++) {
		pg_rigidbody *rb;
		rb = pg_vector_ptrs_at(&pg->rigid_bodies, i);
		pg_assert(rb);
		pg_rigidbody_integrate(rb, time_delta);
	}
}

void playground_add_body(playground *pg, pg_rigidbody *body) {
	pg_assert(pg && body);
	pg_vector_ptrs_push_back(&pg->rigid_bodies, body);
}

