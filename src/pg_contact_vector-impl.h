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


__pg_inline__ void pg_contact_vector_init(struct pg_contact_vector *v)
{
	pg_assert(v);
	pg_array_container_init(&v->ac, sizeof(pg_contact));
}

__pg_inline__ void pg_contact_vector_deinit(struct pg_contact_vector *v)
{
	pg_assert(v);
	pg_array_container_deinit(&v->ac);
}


__pg_inline__ pg_contact*
pg_contact_vector_get_ptr_at(struct pg_contact_vector *v, unsigned int at) {
	pg_assert(v && (at < v->ac.size));
	return &((pg_contact*) v->ac.mblock.mem)[at];
}


__pg_inline__ void pg_contact_vector_clear(struct pg_contact_vector *v) {
	pg_assert(v);
	pg_array_container_clear(&v->ac, sizeof(void*));
}


__pg_inline__ pg_contact_vector *v
pg_contact_vector_append_contact_uninitialized(struct pg_contact_vector *v) {
	pg_contact *c;
	pg_assert(v);
	/* check for the need of more memory */
	pg_array_container_check_size_and_grow(&v->ac);
	c = &((pg_contact*) v->ac.mblock.mem)[v->ac.size];
	v->ac.size ++;
}


__pg_inline__ unsigned int pg_contact_vector_reserved(struct pg_contact_vector *v) {
	pg_assert(v);
	return v->ac.reserved;
}


