/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:41:38 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/15 15:21:13 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray_x_obj	ray_x_plane(t_ray ray, t_plane const *pl)
{
	t_flt	t;
	t_flt	divisor;

	ray = transformed_ray(ray, pl->inverse);
	divisor = dot(ray.dir, pl->orientation);
	if (floats_are_equal(divisor, 0))
		return ((t_ray_x_obj){0});
	t = dot(vec_sub(pl->pos, ray.orig), pl->orientation) / divisor;
	if (t < 0)
		return ((t_ray_x_obj){0});
	return ((t_ray_x_obj){.t = t, .obj = (void *)pl, .obj_type = PLANE});
}

t_vec4	plane_normal(t_plane pl, t_ray ray)
{
	t_vec4	normal;

	normal = transformed_vec(pl.orientation, pl.inverse);
	if (dot(ray.dir, pl.orientation) > 0)
		normal = opposite_vec(normal);
	return (normal);
}
