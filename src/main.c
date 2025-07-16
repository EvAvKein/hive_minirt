/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:52:22 by ekeinan           #+#    #+#             */
/*   Updated: 2025/07/11 10:16:31 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @returns A pointer to the program's data.
 */
t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}

int	main(int argc, char **argv)
{
	t_data *const	data = get_data();

	if (argc != 2)
	{
		print_err("program must be provided a single argument");
		return (1);
	}
	if (!parse_scene(argv[1]))
		return (free_data());
	if (data_init_successful() == false)
		return (data->error);
	init_transforms();
	setup_pixel_rays();
	set_vertical_gradient(data->img, (t_float_color[2]){
		(t_float_color){.r = .1, .g = 1, .b = 1, .a = 1},
		(t_float_color){.r = 1, .g = 1, .b = 1, .a = 1}
	});
	cast_rays();
	mlx_key_hook(data->mlx, keyhook, NULL);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	free_data();
	return (0);
}
