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


__pg_inline__ void pg_rigidbody_vector_init(struct pg_rigidbody_vector *v) {
	pg_assert(v);
	pg_array_container_init(&v->ac, PG_RIGIDBODY_VECTOR__SLOT_SIZE);
}


__pg_inline__ void pg_rigidbody_vector_deinit(struct pg_rigidbody_vector *v) {
	pg_assert(v);
	pg_array_container_deinit(&v->ac);
}


__pg_inline__ pg_rigidbody*
pg_rigidbody_vector_get_ptr_at(struct pg_rigidbody_vector *v, unsigned int at) {
	pg_assert(v && (at < v->ac.size));
	return (pg_rigidbody*)&((char*) v->ac.mblock.mem)[at*PG_RIGIDBODY_VECTOR__SLOT_SIZE];
}


__pg_inline__ void pg_rigidbody_vector_clear(struct pg_rigidbody_vector *v) {
	pg_assert(v);
	pg_array_container_clear(&v->ac, sizeof(void*));
}


__pg_inline__ pg_rigidbody_vector *v
pg_rigidbody_vector_append_rigidbody_uninitialized(struct pg_rigidbody_vector *v) {
	pg_rigidbody *rb;
	pg_assert(v);
	/* check for the need of more memory */
	pg_array_container_check_size_and_grow(&v->ac);
	rb = pg_rigidbody*&((char*) v->ac.mblock.mem)[v->ac.size*PG_RIGIDBODY_VECTOR__SLOT_SIZE];
	v->ac.size ++;
}


__pg_inline__ unsigned int pg_rigidbody_vector_reserved(struct pg_rigidbody_vector *v) {
	pg_assert(v);
	return v->ac.reserved;
}


