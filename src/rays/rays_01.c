/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:48:44 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/15 13:44:45 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @returns	Ray transformed by transformation matrix
 */
t_ray	transformed_ray(t_ray ray, t_m4x4 transform)
{
	ray.dir = transformed_vec(ray.dir, transform);
	ray.orig = transformed_vec(ray.orig, transform);
	return (ray);
}

/**
 @returns	Vector reflected by normal
 */
t_vec4	reflection(t_vec4 vec, t_vec4 normal)
{
	t_vec4	reflected;

	reflected = scaled_vec(normal, 2 * dot(vec, normal));
	reflected = vec_sub(vec, reflected);
	return (reflected);
}

/**
 @returns	Position along ray defined by distance value t
 */
inline t_vec4	ray_position(t_ray ray, t_flt t)
{
	return (vec_sum(ray.orig, scaled_vec(ray.dir, t)));
}
