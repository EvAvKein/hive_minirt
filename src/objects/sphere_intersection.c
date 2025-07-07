/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:14:55 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/07 18:01:23 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	ray_intersects_sphere(t_vec4 const *ray, t_sphere const *sp)
{
	t_vec4	sp_pos_neg;
	t_quad	q;

	sp_pos_neg = new_scaled_vec(&sp->pos, -1);
	q.b = 2 * dot_product(ray, &sp_pos_neg);
	q.c = dot_product(&sp_pos_neg, &sp_pos_neg) - sp->radius * sp->radius;
	q.discr = q.b * q.b - 4 * q.c;
	if (q.discr >= 0)
		return (true);
	return (false);
}

t_vec4	closer_sphere_intersection(t_vec4 const *ray, t_sphere const *sp)
{
	t_vec4	sp_pos_neg;
	t_vec4	intersection;
	t_quad	q;
	t_flt	t;

	sp_pos_neg = new_scaled_vec(&sp->pos, -1);
	q.b = 2 * dot_product(ray, &sp_pos_neg);
	q.c = dot_product(&sp_pos_neg, &sp_pos_neg) - sp->radius * sp->radius;
	q.discr = q.b * q.b - 4 * q.c;
	t = -0.5 * (q.b + sqrt(q.discr));
	intersection = new_scaled_vec(ray, t);
	return (intersection);
}
