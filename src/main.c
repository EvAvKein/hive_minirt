/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:52:22 by ekeinan           #+#    #+#             */
/*   Updated: 2025/07/01 15:58:35 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * 
 * @returns A pointer to the program's data.
 * 
 */
t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}

void	write_pixel_rays_to_file(const char *str)
{
	size_t	i;
	t_data	*data;
	int		fds[2];

	fds[0] = open(str, O_CREAT | O_TRUNC | O_WRONLY);
	if (fds[0] < 0)
		return ;
	fds[1] = dup(STDOUT_FILENO);
	dup2(fds[0], STDOUT_FILENO);
	data = get_data();
	i = -1;
	while (++i < data->pixel_count)
		print_vec(&data->pixel_rays[i]);
	fflush(stdout);
	close(fds[0]);
	dup2(fds[1], STDOUT_FILENO);
	close(fds[1]);
}

int	main(int argc, char **argv)
{
	t_data		*data;
	t_sphere	sp;

	if (argc != 2)
	{
		print_err("program must be provided a single argument");
		return (1);
	}
	if (!parse_scene(argv[1]))
	{
		free_data();
		return (1);
	}
	data = get_data();
	if (data_init_successful() == false)
		return (data->error);
	sp = (t_sphere){
		.pos = (t_vec4){.axis.x = 0,
						.axis.y = 0,
						.axis.z = 10,
						.axis.w = 1},
		.radius = 3,
		.next = NULL};
	setup_pixel_rays();
	write_pixel_rays_to_file("rays.log");
	set_uv(data->img);
	for (size_t i = 0; i < data->pixel_count; ++i) {
		if (ray_intersects_sphere(&data->pixel_rays[i], &sp)) {
			data->img->pixels[i * 4] = 0xff;
			data->img->pixels[i * 4 + 1] = 0xff;
			data->img->pixels[i * 4 + 2] = 0xff;
			data->img->pixels[i * 4 + 3] = 0xff;
		}
	}
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	free_data();
	return (0);
}
