/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:48:44 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/09 14:05:15 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	*transform_ray(t_ray *ray, t_m4x4 const *transform)
{
	ray->orig = transformed_vec(&ray->orig, transform);
	ray->dir = transformed_vec(&ray->dir, transform);
	return (ray);
}

t_ray	*inverse_transform_ray(t_ray *ray, t_m4x4 const *transform)
{
	t_m4x4	inverse;

	inverse = inverse_m4x4(transform);
	ray->orig = transformed_vec(&ray->orig, &inverse);
	ray->dir = transformed_vec(&ray->dir, &inverse);
	return (ray);
}

t_ray	transformed_ray(t_ray *ray, t_m4x4 const *transform)
{
	t_ray	transformed;

	transformed.dir = transformed_vec(&ray->dir, transform);
	transformed.orig = transformed_vec(&ray->orig, transform);
	return (transformed);
}

t_vec4	reflection(t_vec4 const *vec, t_vec4 const *normal)
{
	t_vec4	ref;

	ref = scaled_vec(normal, 2 * dot(vec, normal));
	ref = vec_sub(vec, &ref);
	return (ref);
}
