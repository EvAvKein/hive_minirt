/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization_03.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:10:57 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/29 11:11:22 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	setup_pixel_grid(void)
{
	t_data *const		data = get_data();
	t_pixel_grid *const	g = &data->pixel_grid;

	g->fov_h = data->elems.camera->fov * RADIANS_PER_DEGREE;
	g->width = 2 * sin(g->fov_h / 2);
	g->pixel_width = g->width / data->img->width;
	g->height = g->pixel_width * data->img->height;
}

t_ray	ray_for_pixel(size_t i)
{
	t_data *const		data = get_data();
	t_pixel_grid *const	g = &data->pixel_grid;
	t_vec4				pixel_pos;
	size_t				idx[2];

	idx[0] = i % data->img->width;
	idx[1] = i / data->img->width;
	pixel_pos.x = (-g->width + g->pixel_width) / 2 + (idx[0]) * g->pixel_width;
	pixel_pos.y = (g->height - g->pixel_width) / 2 - (idx[1]) * g->pixel_width;
	pixel_pos.z = cos(g->fov_h / 2);
	pixel_pos.w = 0;
	return (transformed_ray((t_ray){
			.orig = point(0, 0, 0),
			. dir = unit_vec(pixel_pos)}, data->elems.camera->transform));
}
