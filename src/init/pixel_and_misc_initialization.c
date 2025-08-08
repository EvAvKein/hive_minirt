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

/**
 * Calculates unit vectors for each ray that is being cast at a specific pixel.
 * Also applies camera transform.
 */
void	setup_pixel_rays(void)
{
	size_t			i;

	setup_pixel_grid();
	i = -1;
	while (++i < g_data.pixel_count)
		g_data.pixel_rays[i] = ray_for_pixel(i);
}

/**
 * Calculates pixel grid variables based on camera fov and the image buffer's
 * dimensions.
 */
void	setup_pixel_grid(size_t width, size_t height)
{
	t_pixel_grid *const	g = &g_data.pixel_grid;

	g_data.pixel_count = width * height;
	g->fov_h = g_data.elems.camera->fov * RADIANS_PER_DEGREE;
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
	t_pixel_grid *const	g = &g_data.pixel_grid;
	t_vec4				pixel_pos;
	size_t				idx[2];

	idx[0] = i % g_data.img->width;
	idx[1] = i / g_data.img->width;
	pixel_pos.x = (-g->width + g->pixel_width) / 2 + (idx[0]) * g->pixel_width;
	pixel_pos.y = (g->height - g->pixel_width) / 2 - (idx[1]) * g->pixel_width;
	pixel_pos.z = cos(g->fov_h / 2);
	pixel_pos.w = 0;
	return (transformed_ray((t_ray){
			.orig = point(0, 0, 0),
			.dir = unit_vec(pixel_pos),
			.closest_hit.t = MAX_DIST}, g_data.elems.camera->transform));
}

void	init_object_data(void)
{
	init_lights(g_data.elems.lights);
	init_spheres(g_data.elems.spheres);
	init_planes(g_data.elems.planes);
	init_cylinders(g_data.elems.cylinders);
	init_triangles(g_data.elems.triangles);
	init_camera_transform(g_data.elems.camera);
}
