/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:33:47 by jvarila           #+#    #+#             */
/*   Updated: 2025/08/07 10:37:44 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
 * Checks for exit and screenshot keypresses.
 */
void	exit_and_screenshot_hook(mlx_key_data_t key_data, void *param)
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
	if (mlx_is_key_down(data->mlx, KEYBIND_SAVE))
	{
		image_to_file("miniRT.bmp");
		return ;
	}
}

void	resize_hook(int32_t width, int32_t height, void *param)
{
	((t_data *)param)->pause_threads = true;
	while (g_data.active_threads != 0)
		usleep (TICK);
	mlx_resize_image(g_data.img, width, height);
	setup_pixel_grid(width, height);
	wait_for_threads_and_restart();
}
