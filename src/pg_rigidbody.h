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

#ifndef pg_rigidbody_h
#define pg_rigidbody_h

#include <memory.h>
#include "la.h"
#include "pg_debug.h"
#include "pg_config.h"

typedef struct pg_rigidbody {
	/* private */
	lav3 force_accumulator;       /* force accumulator                    */
	lav3 acceleration;            /* linear acceleration in world frame   */
	lav3 velocity;                /* linear velocity in world frame       */
	lav3 position;                /* position in world frame              */
	las inverse_mass;             /* inverse body-mass                    */
} pg_rigidbody;


__pg_inline__ void pg_rigidbody_init(pg_rigidbody *rb);
__pg_inline__ void pg_rigidbody_set_position(pg_rigidbody *rb, const lav3 *pos);
__pg_inline__ void pg_rigidbody_set_velocity(pg_rigidbody *rb, const lav3 *vel);
__pg_inline__ void pg_rigidbody_set_acceleration(pg_rigidbody *rb, const lav3 *acc);
__pg_inline__ void pg_rigidbody_set_mass(pg_rigidbody *rb, las mass);
__pg_inline__ void pg_rigidbody_set_mass_to_infinity(pg_rigidbody *rb);

//__pg_inline__ void pg_rigidbody_set_vel_damping(pg_rigidbody *rb, las damping);

/* F to be expressed in the world frame */
__pg_inline__ void pg_rigidbody_add_force(pg_rigidbody *rb, const lav3 *F);

__pg_inline__ void pg_rigidbody_integrate(pg_rigidbody *rb, las time_delta);


#include "pg_rigidbody-impl.h"

#endif /* pg_rigidbody_h */

