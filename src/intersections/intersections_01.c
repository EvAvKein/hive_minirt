/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_01.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:51:09 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/18 17:15:30 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	xinit_ray_intersections(t_ray *ray)
{
	ray->intersections.capacity = 8;
	ray->intersections.idx = 0;
	ray->intersections._ = xcalloc(8, sizeof(t_ray_x_obj));
}

void	xadd_intersection(t_ray *ray, t_ray_x_obj intersection)
{
	t_ray_x_obj	*temp;

	if (ray->intersections.capacity == 0)
		xinit_ray_intersections(ray);
	if (ray->intersections.idx >= ray->intersections.capacity)
	{
		temp = xcalloc(ray->intersections.capacity * 2, sizeof(t_ray_x_obj));
		ft_memcpy(temp, ray->intersections._,
			ray->intersections.idx * sizeof(t_ray_x_obj));
		free(ray->intersections._);
		ray->intersections._ = temp;
		ray->intersections.capacity *= 2;
	}
	ray->intersections._[ray->intersections.idx++] = intersection;
}

void	empty_intersections(t_ray *ray)
{
	if (ray->intersections._)
	{
		ft_bzero(ray->intersections._, ray->intersections.idx
			* sizeof(t_ray_x_obj));
		ray->intersections.idx = 0;
		return ;
	}
	ray->intersections = (t_ray_x_obj_array){0};
}
