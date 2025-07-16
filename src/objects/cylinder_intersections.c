/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:01:58 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/16 15:12:53 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_quad	solve_cylinder_quadratic(t_ray ray, t_cylinder cyl)
{
	t_quad	q;

	q.a = pow(ray.dir._[0], 2) + pow(ray.dir._[2], 2);
	if (floats_are_equal(q.a, 0))
		return ((t_quad){0});
	q.b = 2 * ray.orig._[0] * ray.dir._[0] + 2 * ray.orig._[2] * ray.dir._[2];
	q.c = pow(ray.orig._[0], 2) + pow(ray.orig._[2], 2) - pow(cyl.diam / 2, 2);
	q.discr = q.b * q.b - 4 * q.a * q.c;
	if (q.discr < 0)
		return ((t_quad){0});
	return (q);
}

bool	ray_hits_cylinder(t_ray ray, t_cylinder cyl)
{
	t_quad	q;

	q.a = pow(ray.dir._[0], 2) + pow(ray.dir._[2], 2);
	if (floats_are_equal(q.a, 0))
		return (false);
	q.b = 2 * ray.orig._[0] * ray.dir._[0] + 2 * ray.orig._[2] * ray.dir._[2];
	q.c = pow(ray.orig._[0], 2) + pow(ray.orig._[2], 2) - pow(cyl.diam / 2, 2);
	q.discr = q.b * q.b - 4 * q.a * q.c;
	if (q.discr < 0)
		return (false);
	return (true);
}
