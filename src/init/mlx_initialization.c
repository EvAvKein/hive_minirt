/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_initialization.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:55:52 by jvarila           #+#    #+#             */
/*   Updated: 2025/08/08 17:15:37 by ekeinan          ###   ########.fr       */
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
	dat()->pixel_count = RES_X * RES_Y;
	init_object_data();
	if (mlx_init_successful() == false)
		return (false);
	if (mlx_asset_init_successful() == false)
		return (false);
	return (true);
}

/**
 * Attempts to set up the mlx window and image buffer. If something goes wrong
 * sets dat()->error and terminates mlx.
 *
 * @returns	true if mlx is initialized succesfully, false on error
 */
static bool	mlx_init_successful(void)
{
	dat()->mlx = mlx_init(RES_X, RES_Y, "miniRT", true);
	if (dat()->mlx == NULL)
		return (set_error_return_false(ERROR_MLX_INIT));
	dat()->img = mlx_new_image(dat()->mlx, RES_X, RES_Y);
	if (dat()->img == NULL)
	{
		mlx_terminate(dat()->mlx);
		return (set_error_return_false(ERROR_MLX_NEW_IMAGE));
	}
	if (mlx_image_to_window(dat()->mlx, dat()->img, 0, 0) < 0)
	{
		mlx_terminate(dat()->mlx);
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
		ft_putendl_fd("ERROR: problem_with_resolution: "
			"invalid width or height", STDERR_FILENO);
		return (true);
	}
	if (RES_X > SIZE_MAX / RES_Y || RES_Y > SIZE_MAX / RES_X)
	{
		ft_putendl_fd("ERROR: problem_with_resolution: "
			"pixel count overflows SIZE_MAX", STDERR_FILENO);
		return (true);
	}
	return (false);
}

/**
 * @returns	false
 */
static bool	set_error_return_false(t_error error)
{
	dat()->error = error;
	return (false);
}
