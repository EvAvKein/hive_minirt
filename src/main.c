/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:52:22 by ekeinan           #+#    #+#             */
/*   Updated: 2025/08/08 10:49:57 by jvarila          ###   ########.fr       */
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
	setup_pixel_grid(g_data.img->width, g_data.img->height);
	run_threads();
	mlx_close_hook(g_data.mlx, close_hook, &g_data);
	mlx_key_hook(g_data.mlx, exit_and_screenshot_hook, &g_data);
	mlx_loop_hook(g_data.mlx, every_frame, &g_data);
	mlx_resize_hook(g_data.mlx, resize_hook, &g_data);
	mlx_loop(g_data.mlx);
	mlx_terminate(g_data.mlx);
	free_data();
	return (0);
}

static void	load_sky_texture(void)
{
	mlx_texture_t	*tex;

	tex = mlx_load_png("textures/qwantani_dusk_2_puresky.png");
	g_data.sky_texture = mlx_texture_to_image(g_data.mlx, tex);
	mlx_delete_texture(tex);
}
