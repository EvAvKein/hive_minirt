/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_and_misc_initialization.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:10:57 by jvarila           #+#    #+#             */
/*   Updated: 2025/08/11 10:42:45 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Calculates pixel grid variables based on camera fov and the image buffer's
 * dimensions.
 */
void	setup_pixel_grid(size_t width, size_t height)
{
	t_pixel_grid *const	g = &dat()->pixel_grid;

	dat()->pixel_count = width * height;
	g->fov_h = dat()->elems.camera->fov * RADIANS_PER_DEGREE;
	g->width = 2 * sin(g->fov_h / 2);
	g->pixel_width = g->width / width;
	g->height = g->pixel_width * height;
}

/**
 * Calculates ray for specific pixel. The ray is initially set to start from
 * (0, 0, 0) towards the positive z axis direction and then it is transformed
 * to originate from the camera and in the camera's direction.
 *
 * @returns	Ray for pixel with index i
 */
t_ray	ray_for_pixel(size_t i)
{
	t_pixel_grid *const	g = &dat()->pixel_grid;
	t_vec4				pixel_pos;
	size_t				idx[2];

	idx[0] = i % dat()->img->width;
	idx[1] = i / dat()->img->width;
	pixel_pos.x = (-g->width + g->pixel_width) / 2 + (idx[0]) * g->pixel_width;
	pixel_pos.y = (g->height - g->pixel_width) / 2 - (idx[1]) * g->pixel_width;
	pixel_pos.z = cos(g->fov_h / 2);
	pixel_pos.w = 0;
	return (transformed_ray((t_ray){
			.orig = point(0, 0, 0),
			.dir = unit_vec(pixel_pos),
			.closest_hit.t = MAX_DIST}, dat()->elems.camera->transform));
}

/**
 * TODO: Implement init_cones
 */
void	init_object_data(void)
{
	init_lights(g_data.elems.lights);
	init_spheres(g_data.elems.spheres);
	init_planes(g_data.elems.planes);
	init_cylinders(g_data.elems.cylinders);
	// init_cones(g_data.elems.cones);
	init_triangles(g_data.elems.triangles);
	init_camera_transform(g_data.elems.camera);
}
