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

#ifndef pg_contact_solver_h
#define pg_contact_solver_h

#include "las.h"
#include "pg_contact.h"
#include "pg_debug.h"
#include "pg_array_container.h"

/* TBD: arbitrary number for now */
#define PG_CONTACT_SOLVER_MAX_ITERATIONS_DEFAULT 4096 

typedef struct pg_contact_solver {
	unsigned int max_iterations;  /* upper bound on solver iterations */
	unsigned int used_iterations; /* track number of used iterations  */

} pg_contact_solver;


__pg_inline__ void pg_contact_solver_init(pg_contact_solver *s,
                                          unsigned int max_iterations);

__pg_inline__ void pg_contact_solver_set_iterations(pg_contact_solver *s,
                                                    unsigned int i);

__pg_inline__ void pg_contact_solver_solve_contacts(pg_contact_solver *s,
                                                    pg_vector_ptrs *contacts,
                                                    las time_delta);

__pg_inline__ void pg_contact_solver_init(pg_contact_solver *s,
                                          unsigned int max_iterations) {
	pg_assert(s && max_iterations >0);
	if (!max_iterations)
		max_iterations = PG_CONTACT_SOLVER_MAX_ITERATIONS_DEFAULT;

	s->max_iterations = max_iterations;
	s->used_iterations = 0;
}

__pg_inline__ void pg_contact_solver_set_iterations(pg_contact_solver *s,
                                                    unsigned int max_iterations) {
	pg_assert(s && max_iterations >0);
	if (max_iterations)
		s->max_iterations = max_iterations;
}


__pg_inline__ void pg_contact_solver_solve_contacts(pg_contact_solver *s,
                                                    pg_vector_ptrs *contacts,
                                                    las time_delta) {
	unsigned int num_contacts;
	pg_assert(s && contacts);
	s->used_iterations = 0;
	num_contacts = pg_vector_ptrs_size(contacts);
 
	pg_assert(s->max_iterations>=2*num_contacts);
	/* TBD: max_iterasions should be tuned based on the number of contacts
	   otherwise there might be cases where some contacts don't get a chance
	   of getting solved */

	while(s->used_iterations < s->max_iterations) {
		/* solve contacts starting from the one with largest closing velocity */
		unsigned int i;
		pg_contact *max_sep_vel_contact;
		las max_sep_vel;
    
		max_sep_vel_contact = NULL;
		max_sep_vel = 0.;

		for (i = 0; i < num_contacts; i++) {
			pg_contact* c;
			las sep_vel;
      
			c = pg_vector_ptrs_at(contacts, i);
			pg_assert(c);
			sep_vel = pg_contact_separating_vel(c);
			if (sep_vel < max_sep_vel) {
				max_sep_vel = sep_vel;
				max_sep_vel_contact = c;
			}
		}
		/* resolve this contact */
		pg_contact_resolve(max_sep_vel_contact, time_delta);
		s->used_iterations++;
	}
}

#endif /* pg_contact_solver_h */

