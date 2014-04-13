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

__pg_inline__ void pg_particle_set_pos(pg_particle *p, lav3 *pos) {
	pg_assert(p && pos);
	lav3_copy(&p->pos, pos);
}

__pg_inline__ void pg_particle_set_vel(pg_particle *p, lav3 *vel) {
	pg_assert(p && vel);
	lav3_copy(&p->vel, vel);
}

__pg_inline__ void pg_particle_set_acc(pg_particle *p, lav3 *acc) {
	pg_assert(p && acc);
	lav3_copy(&p->acc, acc);
}

__pg_inline__ void pg_particle_set_mass(pg_particle *p, las mass) {
	pg_assert(p && mass!=0.);
	p->inv_mass = 1./mass;
}

__pg_inline__ void pg_particle_set_mass_infinity(pg_particle *p) {
	pg_assert(p);
	p->inv_mass = 0.;
}


__pg_inline__ void pg_particle_set_vel_damping(pg_particle *p, las damping) {
	pg_assert(p && damping >= 0.);
	p->vel_damping = damping;
}

__pg_inline__ void pg_particle_clear_force_accu(pg_particle *p) {
	pg_assert(p);
	lav3_set_zero(&p->force_accu);
}

__pg_inline__ void pg_particle_add_force(pg_particle *p, lav3 *F) {
	pg_assert(p && F);
	lav3_ipadd(&p->force_accu, F);
}

__pg_inline__ void pg_particle_integrate(pg_particle *p, las time_delta) {
	pg_assert(p && time!=0.);

	/* acceleration */
	lav3_ipadd_scaled(&p->acc, &p->force_accu, p->inv_mass);

	/* velocity with damping */
	lav3_ipadd_scaled(&p->vel, &p->acc, time_delta);
	lav3_smul(&p->vel, la_pow(p->vel_damping, time_delta));

	/* position */
	lav3_ipadd_scaled(&p->pos, &p->vel, time_delta);
	lav3_ipadd_scaled(&p->pos, &p->acc, time_delta*time_delta*0.5);

	/* TBD to be really put here ?*/
	pg_particle_clear_force_accu(p);
}

#endif /* pg_particle_h */

