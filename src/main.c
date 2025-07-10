/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:52:22 by ekeinan           #+#    #+#             */
/*   Updated: 2025/07/10 11:48:59 by jvarila          ###   ########.fr       */
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
	{
		free_data();
		return (1);
	}
	if (data_init_successful() == false)
		return (data->error);

// -----------------------------------------------------------------------------
	// Open engine, will organize code into logical chuncks and pack them away
	// as functionality gradually improves

	data->elems.camera->orientation = vector(0, 0, 1);
	setup_pixel_rays();
	set_uv(data->img);

	t_sphere	sp;
	sp.pos = position(0, 0, 30);
	sp.radius = 3;
	sp.transform = identity_m4x4();
	sp.inverse = inverse_m4x4(sp.transform);
	sp.material = default_material();
	sp.material.color = (t_vec4){
		.axis.x = 1,
		.axis.y = 0,
		.axis.z = 1,
		.axis.w = 1,
	};
	sp.material.ambient = .2;
	t_light	light;
	light.pos = position(20, 80, -10);
	light.color = (t_color){.bit = (t_8bit_color){.rgba = 0xffffffff}};
	light.brightness = 1;
	light.transform = identity_m4x4();
	light.color.flt = color_8bit_to_float(light.color.bit);

	t_ray			ray;
	t_phong_helper	p;
	t_color			color;
	p = (t_phong_helper){0};
	(void)color;
	p.mat = &sp.material;
	p.light = &light;
	for (size_t i = 0; i < data->pixel_count; ++i)
	{
		ray = data->pixel_rays[i];
		p.to_cam = scaled_vec(ray.dir, -1);
		t_rxos	rxos = ray_x_sphere(ray, &sp);
		t_rxo	rxo = hit(rxos);
		if (rxo.t <= 0)
			continue ;
		p.pos = scaled_vec(ray.dir, rxo.t);
		p.normal = sphere_normal_at(sp, ray, rxo);
		color = let_there_be_light(&p);
		// data->img->pixels[i * 4 + 0] = (p.normal._[0] * 0.5 + 0.5) * 255.999 * 1;
		// data->img->pixels[i * 4 + 1] = (p.normal._[1] * 0.5 + 0.5) * 255.999 * 1;
		// data->img->pixels[i * 4 + 2] = (-p.normal._[2] * 0.5 + 0.5) * 255.999 * 1;
		// data->img->pixels[i * 4 + 3] = 0xff;
		data->img->pixels[i * 4 + 0] = color.bit.channel.r;
		data->img->pixels[i * 4 + 1] = color.bit.channel.g;
		data->img->pixels[i * 4 + 2] = color.bit.channel.b;
		data->img->pixels[i * 4 + 3] = 0xff;
	}
// -----------------------------------------------------------------------------
	image_to_file("miniRT.bmp");
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	free_data();
	return (0);
}
