/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization_01.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:55:52 by jvarila           #+#    #+#             */
/*   Updated: 2025/06/26 15:12:09 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	mlx_init_successful(void);
static bool	problem_with_resolution(void);
static bool	set_error_return_false(enum e_error error);

/**
 * Attempts to initialize data structure before running the raytracer.
 *
 * @returns	true when data initialization is succesfull, false on error
 */
bool	data_init_successful(void)
{
	t_data	*data;

	data = get_data();
	if (problem_with_resolution())
		return (set_error_return_false(ERROR_PROBLEM_WITH_RESOLUTION));
	data->pixel_count = RES_X * RES_Y;
	data->pixel_rays = malloc(data->pixel_count * sizeof(t_vec4));
	if (data->pixel_rays == NULL)
		return (set_error_return_false(ERROR_ALLOC));
	if (mlx_init_successful() == false)
		return (false);
	return (true);
}

/**
 * Calculates unit vectors for each ray that is being cast at a specific pixel.
 */
void	setup_pixel_rays(void)
{
	t_data			*data;
	t_pixel_grid	g;
	t_vec4			pixel;
	size_t			idx[3];

	data = get_data();
	g.fov_h = 90 * RADIANS_PER_DEGREE;
	g.fov_v = 2 * atan(tan(g.fov_h / 2) * RES_Y / RES_X);
	g.width = 2 * sin(g.fov_h / 2);
	g.height = 2 * sin(g.fov_v / 2);
	g.pixel_width = g.width / RES_X;
	pixel.axis.z = cos(g.fov_h / 2);
	pixel.axis.w = 0;
	idx[0] = -1;
	while (++idx[0] < data->pixel_count)
	{
		idx[1] = idx[0] % RES_X;
		idx[2] = idx[0] / RES_X;
		pixel.axis.x = (-g.width + g.pixel_width) / 2 + idx[1] * g.pixel_width;
		pixel.axis.y = (g.height - g.pixel_width) / 2 - idx[2] * g.pixel_width;
		pixel.axis.z = cos(g.fov_h / 2);
		pixel.axis.w = 0;
		data->pixel_rays[idx[0]] = new_unit_vector(&pixel);
	}
}

/**
 * Attempts to set up the mlx window and image buffer. If something goes wrong
 * sets data->error and terminates mlx.
 *
 * @returns	true if mlx is initialized succesfully, false on error
 */
static bool	mlx_init_successful(void)
{
	t_data	*data;

	data = get_data();
	data->mlx = mlx_init(RES_X, RES_Y, "miniRT", 1);
	if (data->mlx == NULL)
		return (set_error_return_false(ERROR_MLX_INIT));
	data->img = mlx_new_image(data->mlx, RES_X, RES_Y);
	if (data->img == NULL)
	{
		mlx_terminate(data->mlx);
		return (set_error_return_false(ERROR_MLX_NEW_IMAGE));
	}
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0)
	{
		mlx_terminate(data->mlx);
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
static bool	set_error_return_false(enum e_error error)
{
	get_data()->error = error;
	return (false);
}
