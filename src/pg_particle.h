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

#ifndef pg_particle_h
#define pg_particle_h

#include <memory.h>
#include "las.h"
#include "lav3.h"
#include "pg_debug.h"
#include "pg_config.h"

typedef struct pg_particle {
	lav3 pos;        /* position            */
	lav3 vel;        /* linear velocity     */
	lav3 acc;        /* linear acceleration */
	lav3 force_accu; /* force accumulator   */
	las vel_damping; /* velocity damping    */
	las inv_mass;    /* particle-mass^-1    */
} pg_particle;


__pg_inline__ void pg_particle_set_pos(pg_particle *p, lav3 *pos);
__pg_inline__ void pg_particle_set_vel(pg_particle *p, lav3 *vel);
__pg_inline__ void pg_particle_set_acc(pg_particle *p, lav3 *acc);
__pg_inline__ void pg_particle_set_mass(pg_particle *p, las mass);
__pg_inline__ void pg_particle_set_mass_infinity(pg_particle *p);
__pg_inline__ void pg_particle_set_vel_damping(pg_particle *p, las damping);

__pg_inline__ void pg_particle_clear_force_accu(pg_particle *p);
__pg_inline__ void pg_particle_add_force(pg_particle *p, lav3 *F);
__pg_inline__ void pg_particle_integrate(pg_particle *p, las time_delta);


#endif /* pg_particle_h */

