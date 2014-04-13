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

#ifndef pg_collide_h
#define pg_collide_h

#include <stdlib.h>
#include "pg_collision.h"
#include "pg_debug.h"
#include "pg_config.h"

__pg_inline__ int pg_collide_sphere_sphere(pg_collision *collision,
                                           pg_sphere *a,
                                           pg_sphere *b);

__pg_inline__ int pg_collide_sphere_plane(pg_collision *collision,
                                          pg_sphere *sphere,
                                          pg_plane *plane);

#include "pg_collide-impl.h"

#endif /* pg_collide_h */

