/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:33:47 by jvarila           #+#    #+#             */
/*   Updated: 2025/08/15 13:36:28 by jvarila          ###   ########.fr       */
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
	if (mlx_is_key_down(dat()->mlx, KEYBIND_FOV_INC))
		fov_delta = FOV_DELTA;
	else if (mlx_is_key_down(dat()->mlx, KEYBIND_FOV_DEC))
		fov_delta = -FOV_DELTA;
	if (mlx_is_key_down(dat()->mlx, KEYBIND_FAST))
		fov_delta *= 2;
	if (fov_delta == 0
		|| dat()->elems.camera->fov + fov_delta > 180
		|| dat()->elems.camera->fov + fov_delta < 1)
		return ;
	dat()->pause_threads = true;
	dat()->elems.camera->fov += fov_delta;
	setup_pixel_grid(dat()->img->width, dat()->img->height);
	printf("Camera FOV:		%u\n", dat()->elems.camera->fov);
	reset_rendering_threads();
}

/**
 * Hook for stopping the threads before closing the mlx window.
 */
void	close_hook(void *param)
{
	t_data *const	data = param;

	data->stop_threads = true;
	while (data->active_threads > 0)
		usleep(TICK * 10);
}

/**
 * Checks for exit and screenshot and cap-toggling keypresses.
 */
void	exit_and_screenshot_and_capping_hook(
			mlx_key_data_t key_data, void *param)
{
	(void)param;
	(void)key_data;
	if (mlx_is_key_down(dat()->mlx, KEYBIND_QUIT))
	{
		dat()->stop_threads = true;
		while (dat()->active_threads > 0)
			usleep(TICK * 10);
		mlx_close_window(dat()->mlx);
	}
	else if (mlx_is_key_down(dat()->mlx, KEYBIND_NO_CAP))
	{
		dat()->no_cap = !dat()->no_cap;
		reset_rendering_threads();
	}
	else if (mlx_is_key_down(dat()->mlx, KEYBIND_SAVE))
		image_to_file();
	else if (mlx_is_key_down(dat()->mlx, KEYBIND_RESET)
		&& !mlx_is_key_down(dat()->mlx, KEYBIND_OBJ))
		reset_camera();
	else if (mlx_is_key_down(dat()->mlx, KEYBIND_RESET)
		&& !mlx_is_key_down(dat()->mlx, KEYBIND_FAST))
		reset_object();
	else if (mlx_is_key_down(dat()->mlx, KEYBIND_RESET))
		reset_scene();
}

/**
 * Sets dat()->resized to true when a window resize event happens,
 * the every_frame hook function takes care of resizing.
 */
void	resize_hook(int32_t width, int32_t height, void *param)
{
	(void)param;
	(void)height;
	(void)width;
	dat()->resized = true;
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
		dat()->thread_can_proceed[i] = false;
	while (dat()->active_threads != 0)
		usleep(TICK);
	i = -1;
	while (++i < THREADS)
		dat()->thread_can_proceed[i] = true;
	dat()->jobs_available = THREADS;
	dat()->pause_threads = false;
}
