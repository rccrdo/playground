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


__pg_inline__ int pg_collide_sphere_sphere(pg_collision *collision, pg_sphere *a, pg_sphere *b) {
	lav3 d;
	las distance;
	las radius_sum;
	pg_contact *contact;
    
	pg_assert(collision && a && b);

	lav3_sub(&d, &a->pos, &b->pos);
	distance = lav3_norm(&d);
  
	/* check for a contact */
	radius_sum = a->radius + b->radius;
	if (d <= 0. || d >= radius_sum)
		return 0;

	/* recover the normal from d */
	lav3_ipsmul(&d, 1./distance);
	contact = malloc(sizeof(pg_contact));

	if (contact == NULL)
		return -1;
  
	lav3_copy(&contact->normal, d);
  
	lav3_ipadd_scaled(&d, &a->pos, 0.5);
	lav3_copy(&contact->point, &d);  
  
	contact->inter_penetration = (radius_sum - distance);

	contact->objs[0] = a;
	contact->objs[1] = b;

	contact->restitution = collision->restitution;
	contact->friction = collision->friction;
	pg_vector_ptrs_append(&collision->contacts, contact);
	return 1;
}

__pg_inline__ int pg_collide_sphere_plane(pg_collision *collision,
					  pg_sphere *sphere,
					  pg_plane *plane) {
	las center_distance;
	pg_contact *contact;
    
	pg_assert(collision && sphere && plane);

	center_distance = lav3_dot(&plane->normal, &sphere->pos) - plane->offset;
	/* check for a contact */
	if (center_distance*center_distance > sphere->radius*sphere->radius)
		return 0;

	contact = malloc(sizeof(pg_contact));
	if (contact == NULL)
		return -1;

	lav3_sub_scaled(&point, &sphere->pos, &plane->normal, center_distance);

	/* check on which side of the plane the sphere is */
	if (center_distance < 0.) {
		lav3_smul(&contact->normal, &plane->normal, -1.);
		contact->inter_penetration = -center_distance + sphere->radius;
	} else {
		lav3_copy(&contact->normal, &plane->normal);
		contact->inter_penetration = center_distance + sphere->radius;
	}

	contact->objs[0] = &sphere->rb;
	contact->objs[1] = NULL;
	contact->restitution = collision->restitution;
	contact->friction = collision->friction;
	return 1;
}

