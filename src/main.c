/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:52:22 by ekeinan           #+#    #+#             */
/*   Updated: 2025/07/09 11:58:29 by jvarila          ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_data *const	data = get_data();

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
	if (data_init_successful() == false)
		return (data->error);

	data->elems.camera->orientation = (t_vec4){._[2] = 1, ._[3] = 1};
	setup_pixel_rays();
	set_uv(data->img);

	t_sphere		sp;
	sp = (t_sphere){
		.pos = (t_vec4){.axis.x = 0,
						.axis.y = 0,
						.axis.z = 30,
						.axis.w = 1},
		.radius = 3,
		.next = NULL,
		.transform = scaling_m4x4(&(t_vec4){
			.axis.x = 1,
			.axis.y = .1,
			.axis.z = 1}),
	};
	sp.inverse = inverse_m4x4(&sp.transform);

	t_ray	ray;
	for (size_t i = 0; i < data->pixel_count; ++i)
	{
		ray = data->pixel_rays[i];
		transform_ray(&ray, &sp.inverse);
		t_rxos	rxos = ray_x_sphere(&ray, &sp);
		t_rxo	intr = hit(&rxos);
		if (intr.t <= 0)
			continue ;
		t_vec4	intr_pos = scaled_vec(&ray.dir, intr.t);
		t_vec4	normal = vec_sub(&intr_pos, &sp.pos);
		normalize_vec(&normal);
		data->img->pixels[i * 4 + 0] = (normal._[0] * 0.5 + 0.5) * 255.999 * 1;
		data->img->pixels[i * 4 + 1] = (normal._[1] * 0.5 + 0.5) * 255.999 * 1;
		data->img->pixels[i * 4 + 2] = (-normal._[2] * 0.5 + 0.5) * 255.999 * 1;
		data->img->pixels[i * 4 + 3] = 0xff;
	}
	image_to_file("miniRT.bmp");
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	free_data();
	return (0);
}
