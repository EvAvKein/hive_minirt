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
	t_data	*data;

	data = get_data();
	if (problem_with_resolution())
		return (set_error_return_false(ERROR_PROBLEM_WITH_RESOLUTION));
	data->pixel_count = RES_X * RES_Y;
	data->pixel_rays = ft_calloc(data->pixel_count, sizeof(t_ray));
	if (data->pixel_rays == NULL)
		return (set_error_return_false(ERROR_ALLOC));
	init_object_data();
	if (mlx_init_successful() == false)
		return (false);
	return (true);
}

/**
 * Calculates unit vectors for each ray that is being cast at a specific pixel.
 * Also applies camera transform.
 */
void	setup_pixel_rays(void)
{
	t_data *const	data = get_data();
	size_t			i;

	setup_pixel_grid();
	i = -1;
	while (++i < data->pixel_count)
		data->pixel_rays[i] = ray_for_pixel(i);
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
	data->mlx = mlx_init(RES_X, RES_Y, "miniRT", true);
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
static bool	set_error_return_false(t_error error)
{
	get_data()->error = error;
	return (false);
}
