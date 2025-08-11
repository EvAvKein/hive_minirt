/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:33:47 by jvarila           #+#    #+#             */
/*   Updated: 2025/08/08 14:46:49 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Checks for FOV change input and updates the camera and pixel grid if
 * necessary.
 */
void	handle_camera_fov_input(void)
{
	t_flt	fov_delta;

	fov_delta = 0;
	if (mlx_is_key_down(g_data.mlx, KEYBIND_FOV_INC))
		fov_delta = FOV_DELTA;
	else if (mlx_is_key_down(g_data.mlx, KEYBIND_FOV_DEC))
		fov_delta = -FOV_DELTA;
	if (mlx_is_key_down(g_data.mlx, KEYBIND_FAST))
		fov_delta *= 2;
	if (fov_delta != 0
		&& g_data.elems.camera->fov + fov_delta <= 180
		&& g_data.elems.camera->fov + fov_delta >= 1)
	{
		g_data.pause_threads = true;
		g_data.elems.camera->fov += fov_delta;
		setup_pixel_grid(g_data.img->width, g_data.img->height);
		reset_rendering_threads();
	}
}

/**
 * Hook for stopping the threads before closing the mlx window.
 */
void	close_hook(void *param)
{
	t_data *const	data = param;

	data->stop_threads = true;
	while (data->active_threads > 0)
		usleep(TICK);
}

/**
 * Checks for exit and screenshot and cap-toggling keypresses.
 */
{
	t_data *const	data = param;

	(void)key_data;
	if (mlx_is_key_down(data->mlx, KEYBIND_QUIT))
	{
		data->stop_threads = true;
		while (data->active_threads > 0)
			usleep(TICK);
		mlx_terminate(g_data.mlx);
		free_data();
		exit(EXIT_SUCCESS);
	}
	if (mlx_is_key_down(data->mlx, KEYBIND_NO_CAP))
	{
		g_data.no_cap = !g_data.no_cap;
		reset_rendering_threads();
		return ;
	}
	if (mlx_is_key_down(data->mlx, KEYBIND_SAVE))
	{
		image_to_file("miniRT.bmp");
		return ;
	}
}

/**
 * Sets g_data.resized to true when a window resize event happens,
 * the every_frame hook function takes care of resizing.
 */
void	resize_hook(int32_t width, int32_t height, void *param)
{
	(void)param;
	(void)height;
	(void)width;
	g_data.resized = true;
}

/**
 * Waits for threads to pause, sets the jobs counter, active threads and
 * unpauses when ready.
 */
void	reset_rendering_threads(void)
{
	size_t	i;

	i = -1;
	while (++i < THREADS)
		g_data.thread_can_proceed[i] = false;
	while (g_data.active_threads != 0)
		usleep(TICK);
	i = -1;
	while (++i < THREADS)
		g_data.thread_can_proceed[i] = true;
	g_data.jobs_available = THREADS;
	g_data.pause_threads = false;
}
