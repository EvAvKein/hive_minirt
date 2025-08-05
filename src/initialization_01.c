/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization_01.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:55:52 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/16 10:21:02 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	mlx_init_successful(void);
static bool	problem_with_resolution(void);
static bool	set_error_return_false(t_error error);

/**
 * Attempts to initialize data structure before running the raytracer.
 *
 * @returns	true when data initialization is succesfull, false on error
 */
bool	data_init_successful(void)
{
	if (problem_with_resolution())
		return (set_error_return_false(ERROR_PROBLEM_WITH_RESOLUTION));
	g_data.pixel_count = RES_X * RES_Y;
	g_data.pixel_rays = ft_calloc(g_data.pixel_count, sizeof(t_ray));
	if (g_data.pixel_rays == NULL)
		return (set_error_return_false(ERROR_ALLOC));
	init_object_data();
	if (mlx_init_successful() == false)
		return (false);
	if (g_data.elems.ambient_light->sky_texture)
	{
		g_data.sky_image = mlx_texture_to_image(g_data.mlx,
				g_data.elems.ambient_light->sky_texture);
		mlx_delete_texture(g_data.elems.ambient_light->sky_texture);
		g_data.elems.ambient_light->sky_texture = NULL;
		if (!g_data.sky_image)
			return (print_err("Failed to convert sky texture to MLX image"));
	}
	return (true);
}

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
 * Attempts to set up the mlx window and image buffer. If something goes wrong
 * sets g_data.error and terminates mlx.
 *
 * @returns	true if mlx is initialized succesfully, false on error
 */
static bool	mlx_init_successful(void)
{
	g_data.mlx = mlx_init(RES_X, RES_Y, "miniRT", true);
	if (g_data.mlx == NULL)
		return (set_error_return_false(ERROR_MLX_INIT));
	g_data.img = mlx_new_image(g_data.mlx, RES_X, RES_Y);
	if (g_data.img == NULL)
	{
		mlx_terminate(g_data.mlx);
		return (set_error_return_false(ERROR_MLX_NEW_IMAGE));
	}
	if (mlx_image_to_window(g_data.mlx, g_data.img, 0, 0) < 0)
	{
		mlx_terminate(g_data.mlx);
		return (set_error_return_false(ERROR_MLX_IMAGE_TO_WINDOW));
	}
	return (true);
}

/**
 * Tests for incorrectly set resolution values.
 *
 * @returns	true if there is a problem with the resolution, false if not
 */
static bool	problem_with_resolution(void)
{
	if (RES_X <= 0 || RES_Y <= 0)
	{
		ft_putstr_fd("ERROR: problem_with_resolution: ", STDERR_FILENO);
		ft_putendl_fd("invalid width or height", STDERR_FILENO);
		return (true);
	}
	if (RES_X > SIZE_MAX / RES_Y || RES_Y > SIZE_MAX / RES_X)
	{
		ft_putstr_fd("ERROR: problem_with_resolution: ", STDERR_FILENO);
		ft_putendl_fd("pixel count overflows SIZE_MAX", STDERR_FILENO);
		return (true);
	}
	return (false);
}

/**
 * @returns	false
 */
static bool	set_error_return_false(t_error error)
{
	g_data.error = error;
	return (false);
}
