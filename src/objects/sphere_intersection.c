/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:14:55 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/01 15:38:35 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	ray_intersects_sphere(t_vec4 const *ray, t_sphere const *sp)
{
	t_flt	a;
	t_flt	b;
	t_flt	c;
	t_flt	discr;
	t_vec4	t;

	t = new_scaled_vec(&sp->pos, -1);
	a = 1;
	b = 2 * dot_product(ray, &t);
	c = dot_product(&t, &t) - sp->radius * sp->radius;
	discr = b * b - 4 * a * c;
	if (discr >= 0)
		return (true);
	return (false);
}
