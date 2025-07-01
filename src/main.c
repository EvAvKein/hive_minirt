/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:52:22 by ekeinan           #+#    #+#             */
/*   Updated: 2025/07/08 11:13:41 by jvarila          ###   ########.fr       */
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
	data->elems.camera->orientation = (t_vec4){._[2] = 1, ._[3] = 1};
	if (data_init_successful() == false)
		return (data->error);

	setup_pixel_rays();
	set_uv(data->img);

	sp = (t_sphere){
		.pos = (t_vec4){.axis.x = 0,
						.axis.y = 0,
						.axis.z = 30,
						.axis.w = 1},
		.radius = 3,
		.next = NULL};

	t_m4x4	transform;
	transform = scaling_m4x4(&(t_vec4){
		.axis.x = 1,
		.axis.y = .1,
		.axis.z = 1,
	});
	transform = inverse_m4x4(&transform);
	t_vec4	transformed_ray;
	for (size_t i = 0; i < data->pixel_count; ++i)
	{
		transformed_ray = transformed_vec(&data->pixel_rays[i], &transform);
		transformed_ray = unit_vec(&transformed_ray);
		t_vec4	intr = primary_sphere_intersection(&transformed_ray, &sp);
		if (!in_front_of_camera(data->elems.camera, &intr))
			continue ;
		t_vec4	normal = vec_sub(&intr, &sp.pos);
		normalize_vec(&normal);
		data->img->pixels[i * 4 + 0] = (normal._[0] * 0.5 + 0.5) * 255.999 * 1;
		data->img->pixels[i * 4 + 1] = (normal._[1] * 0.5 + 0.5) * 255.999 * 1;
		data->img->pixels[i * 4 + 2] = (-normal._[2] * 0.5 + 0.5) * 255.999 * 1;
		data->img->pixels[i * 4 + 3] = 0xff;
	}
	image_to_file("miniRT.bmp");
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
