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

#ifndef pg_contact_h
#define pg_contact_h

#include "las.h"
#include "lav3.h"
#include "pg_particle.h"
#include "pg_debug.h"
#include "pg_memblock.h"
#include "pg_array_container.h"


typedef struct pg_contact {
	pg_rigidbody *objs[2]  /* objects involved in the collision      */
	lav3 point;            /* contact point in world frame           */
	lav3 normal;           /* contact normal in world frame          */
	las inter_penetration; /* inter-penetration between the two objs */
	las restitution;       /* restitution coefficient                */
	las friction;          /* friction coefficient                   */
} pg_contact;


__pg_inline__ las pg_contact_separating_vel(pg_contact *c);
__pg_inline__ void _pg_contact_resolve_vel(pg_contact *c, las time_delta);
__pg_inline__ void pg_contact_resolve_inter_penetration(pg_contact *c, las time_delta);
__pg_inline__ void pg_contact_resolve(pg_contact *c, las time_delta);


__pg_inline__ las pg_contact_separating_vel(pg_contact *c) {
	pg_assert(c);
	pg_assert(0);
	/* write me */
	return 0.;
}

__pg_inline__ void _pg_contact_resolve_vel(pg_contact *c, las time_delta) {
	las separating_vel;
	las new_separating_vel;
	lav3 delta_vel_from_acc;
	las sep_vel_from_acc;
	las delta_vel;
	las total_inv_mass;
	las impulse;
	lav3 impulse_per_unit_inv_mass;
	pg_assert(c);

	/* Find the velocity in the direction of the contact. */
	separating_vel = pg_contact_separating_vel(c);
	/* contact is either separating or stationary */
	if (separating_vel > 0.)
		return;

	/* new separating velocity */
	new_separating_vel = -separating_vel * c->restitution;
  
	/* velocity build-up due to acceleration only */
	lav3_copy(&delta_vel_from_acc, &c->objs[0]->acc);
	if (c->objs[1])
		lav3_ipsub(&delta_vel_from_acc, &c->objs[1]->acc);

	sep_vel_from_acc = time_delta*lav3_dot(&delta_vel_from_acc, &c->normal);

	/* in cas of no closing velocity due to acceleration build-up,
	 * remove it from the new separating velocity */
	if (sep_vel_from_acc < 0.) {
		new_separating_vel += c->restitution * sep_vel_from_acc;
		/* round numerical errors */
		if (new_separating_vel < 0.)
			new_separating_vel = 0.;
	}

	delta_vel = new_separating_vel - separating_vel;

	total_inv_mass = c->objs[0]->inv_mass;
	if (c->objs[1])
		total_inv_mass += c->objs[1]->inv_mass;

	/* If all particles have infinite mass impulses have no effect */
	if (total_inv_mass <= 0.)
		return;

	/* Calculate the impulse to apply. */
	impulse = delta_vel / total_inv_mass;
  
	/* amount of impulse per unit of inverse mass */
	lav3_smul(&impulse_per_unit_inv_mass, &c->normal, impulse);
  
	/* Apply impulses in the direction of the contact */
	lav3_ipadd_scaled(&c->objs[0]->vel,
			  &impulse_per_unit_inv_mass,
			  c->objs[0]->inv_mass);

	if (c->objs[1]) {
		lav3_ipadd_scaled(&c->objs[1]->vel,
				  &impulse_per_unit_inv_mass,
				  -c->objs[1]->inv_mass);
	}
}

__pg_inline__ void pg_contact_resolve_inter_penetration(pg_contact *c,
                                                        las time_delta) {
	lav3 resol_per_unit_inv_mass;
	las total_inv_mass;

	pg_assert(c);

	/* no inter-penetration */
	if (c->inter_penetration <= 0.)
		return;

	total_inv_mass = c->objs[0]->inv_mass;
	if (c->objs[1])
		total_inv_mass += c->objs[1]->inv_mass;
    
	/* if all particles have infinite mass impulses have no effect */
	if (total_inv_mass <= 0.)
		return;

	/* amount of inter-penetration resolution unit of inverse mass */
	lav3_smul(&resol_per_unit_inv_mass,
		  &c->normal,
		  -c->inter_penetration / total_inv_mass);
  
	/* apply the resolution */
	lav3_ipadd_scaled(&c->objs[0]->pos,
			  &resol_per_unit_inv_mass,
			  c->objs[0]->inv_mass);

	if (c->objs[1]) {
		lav3_ipadd_scaled(&c->objs[1]->pos,
				  &resol_per_unit_inv_mass,
				  c->objs[1]->inv_mass);
		/* should we scale by -c->objs[1]->inv_mass !? */
		pg_assert(0);    
	}
}


__pg_inline__ void pg_contact_resolve(pg_contact *c, las time_delta) {
	pg_assert(c && c->objs[0]);
  
	pg_contact_resolve_vel(c, time_delta);
	pg_contact_resolve_inter_penetration(c, time_delta);
}

#endif /* pg_contact_h */

