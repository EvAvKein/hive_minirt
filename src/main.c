/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:52:22 by ekeinan           #+#    #+#             */
/*   Updated: 2025/08/10 17:52:07 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	setup_hooks(void);

/**
 * @returns The program's primary data struct
 */
t_data	*dat(void)
{
	static t_data	data;

	return (&data);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (print_err("program must be provided a single argument"));
	if (!parse_scene(argv[1]))
		return (free_data());
	if (pthread_mutex_init(&dat()->lock, NULL) != 0)
		return (print_err("Couldn't initialize mutex"));
	if (data_init_successful() == false)
		return (dat()->error);
	setup_pixel_grid(dat()->img->width, dat()->img->height);
	run_threads();
	setup_hooks();
	mlx_loop(dat()->mlx);
	free_data();
	mlx_terminate(dat()->mlx);
	return (0);
}

static void	setup_hooks(void)
{
	mlx_close_hook(dat()->mlx, close_hook, dat());
	mlx_key_hook(dat()->mlx, exit_and_screenshot_and_capping_hook, dat());
	mlx_loop_hook(dat()->mlx, every_frame, dat());
	mlx_resize_hook(dat()->mlx, resize_hook, dat());
	mlx_cursor_hook(dat()->mlx, mouse_pos_hook, dat());
	mlx_mouse_hook(dat()->mlx, select_obj_hook, dat());
}
