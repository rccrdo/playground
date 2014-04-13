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


__pg_inline__ void pg_rigidbody_init(pg_rigidbody *rb) {
	pg_assert(rb);
	lav3_set_zero(&rb->force_accumulator);
	lav3_set_zero(&rb->acceleration);
	lav3_set_zero(&rb->velocity);
	lav3_set_zero(&rb->position);
	rb->inverse_mass = 1.;
}

__pg_inline__ void pg_rigidbody_set_position(pg_rigidbody *rb, const lav3 *pos) {
	pg_assert(rb && pos);
	lav3_copy(&rb->position, pos);
}


__pg_inline__ void pg_rigidbody_set_velocity(pg_rigidbody *rb, const lav3 *vel) {
	pg_assert(rb && vel);
	lav3_copy(&rb->velocity, vel);
}


__pg_inline__ void pg_rigidbody_set_acceleration(pg_rigidbody *rb, const lav3 *acc) {
	pg_assert(rb && vel);
	lav3_copy(&rb->acceleration, acc);
}


__pg_inline__ void pg_rigidbody_set_mass(pg_rigidbody *rb, las mass) {
	pg_assert(rb && mass!=0.);
	if (mass == 0.)
		mass = 1.;
	rb->inverse_mass = 1./mass;  
}


__pg_inline__ void pg_rigidbody_set_mass_to_infinity(pg_rigidbody *rb) {
	pg_assert(rb);
	rb->inverse_mass = 0.;
}


__pg_inline__ void pg_rigidbody_add_force(pg_rigidbody *rb, const lav3 *F) {
	pg_assert(rb && F);
	lav3_ipadd(&rb->force_accumulator, F);
}


__pg_inline__ void pg_rigidbody_integrate(pg_rigidbody *rb, las time_delta) {
	lav3 effective_acceleration;
	pg_assert(rb && time!=0.);

	/* velocity with damping */
	lav3_add_scaled(&effective_acceleration,
			&rb->acceleration,
			&rb->force_accumulator,
			rb->inverse_mass);
	lav3_ipadd_scaled(&rb->velocity, &effective_acceleration, time_delta);

	/* position */
	lav3_ipadd_scaled(&rb->position, &rb->velocity, time_delta);
	lav3_ipadd_scaled(&rb->position,
			  &effective_acceleration,
			  time_delta*time_delta*0.5);

	/* angular velocity with damping */

	/* angular position */

	/* clear accumulators for the next iteration */
	lav3_set_zero(&rb->force_accumulator);
}



