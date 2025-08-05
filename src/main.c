/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:52:22 by ekeinan           #+#    #+#             */
/*   Updated: 2025/07/29 12:03:04 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_data	g_data;

int	main(int argc, char **argv)
{
	ft_bzero(&g_data, sizeof(t_data));
	if (argc != 2)
		return (print_err("program must be provided a single argument"));
	if (!parse_scene(argv[1]))
		return (free_data());
	if (pthread_mutex_init(&g_data.lock, NULL) != 0)
		return (print_err("Couldn't initialize mutex"));
	if (data_init_successful() == false)
		return (g_data.error);
	load_sky_texture();
	setup_pixel_grid(g_data.img->width, g_data.img->height);
	run_threads();
	mlx_close_hook(g_data.mlx, close_hook, &g_data);
	mlx_key_hook(g_data.mlx, exit_and_screenshot_hook, &g_data);
	mlx_loop_hook(g_data.mlx, movement_hook, &g_data);
	mlx_loop_hook(g_data.mlx, rotation_hook, &g_data);
	mlx_resize_hook(g_data.mlx, resize_hook, &g_data);
	mlx_loop(g_data.mlx);
	mlx_terminate(g_data.mlx);
	free_data();
	return (0);
}
