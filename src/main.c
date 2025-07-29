/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:52:22 by ekeinan           #+#    #+#             */
/*   Updated: 2025/07/17 10:58:45 by jvarila          ###   ########.fr       */
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

t_color	color_at_obj_hit(t_ray_x_obj *rxo, t_phong_helper *p);

t_color	get_sky_color(t_ray ray)
{
	t_vec2		uv;
	t_color		col;

	uv.x = 0.5 - atan2(ray.dir.z, ray.dir.x) / (2 * M_PI);
	uv.y = 0.5 - asin(ray.dir.y) / M_PI;
	uv.x = (unsigned)(uv.x * 32);
	uv.y = (unsigned)(uv.y * 16);
	uv.x /= 32;
	uv.y /= 16;
	col.flt = (t_float_color){.r = uv.x, .g = uv.y, .a = 1};
	col.bit = color_float_to_8bit(col.flt);
	return (col);
}

void	cast_ray(t_data *data, size_t i, size_t precision)
{
	t_ray *const	ray = &data->pixel_rays[i];
	t_ray_x_obj		*rxo;
	t_phong_helper	p;
	t_color			col;

	p = (t_phong_helper){};
	empty_intersections(ray);
	cast_ray_at_objs(ray, &data->elems, NULL);
	rxo = closest_rxo(&ray->intersections);
	if (rxo == NULL)
		col = get_sky_color(*ray);
	else
	{
		p.light = data->elems.lights;
		p.ray = ray;
		p.pos = ray_position(*ray, rxo->t);
		p.to_cam = opposite_vec(ray->dir);
		p.obj_hit = rxo->obj;
		col = color_at_obj_hit(rxo, &p);
	}
	while (precision--)
		set_pixel_color(i++, col);
}

// TODO: implement
void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_data *const	data = param;

	data->pixel_count = width * height;
	setup_pixel_grid();
	setup_pixel_rays();
}

// TODO: implement
void	close_hook(void)
{
}

void	gradually_render(t_data *data, size_t i0, size_t precision)
{
	size_t	i;

	while (precision > 0)
	{
		i = i0 * precision;
		while (i < data->pixel_count)
		{
			if (data->stop)
				break ;
			cast_ray(data, i, precision);
			i += THREADS * precision;
		}
		precision /= 2;
		++data->threads_waiting;
		while (!(data->threads_waiting == THREADS || data->stop))
			usleep(TICK);
		if (data->stop)
			break ;
		usleep(THREADS * TICK + 10);
		--data->threads_waiting;
	}
}

void	*raycasting_routine(void *arg)
{
	t_data *const	data = arg;
	size_t			i0;
	pthread_t		id;
	size_t			precision;

	pthread_mutex_lock(&data->lock);
	pthread_mutex_unlock(&data->lock);
	id = pthread_self();
	i0 = 0;
	while (id != data->threads[i0])
		++i0;
	precision = 64;
	while ((precision >= data->img->width || precision >= data->img->height)
		&& precision >= 2)
		precision /= 2;
	gradually_render(data, i0, precision);
	--data->active_threads;
	return (NULL);
}

bool	run_threads(t_data *data)
{
	size_t	i;

	i = -1;
	pthread_mutex_lock(&data->lock);
	while (++i < THREADS)
	{
		if (pthread_create(&data->threads[i], NULL,
				&raycasting_routine, (void *)data) != 0)
		{
			pthread_mutex_unlock(&data->lock);
			while (i--)
				pthread_join(data->threads[i], NULL);
			return (print_err("A thread failed to create"));
		}
	}
	data->active_threads = THREADS;
	pthread_mutex_unlock(&data->lock);
	return (true);
}

int	main(int argc, char **argv)
{
	t_data *const	data = get_data();

	if (argc != 2)
		return (print_err("program must be provided a single argument"));
	if (!parse_scene(argv[1]))
		return (free_data());
	if (pthread_mutex_init(&data->lock, NULL) != 0)
		return (print_err("Couldn't initialize mutex"));
	if (data_init_successful() == false)
		return (data->error);
	set_vertical_gradient(data->img, (t_float_color[2]){
		(t_float_color){.r = .1, .g = .8, .b = 1, .a = 1},
		(t_float_color){.r = 1, .g = 1, .b = 1, .a = 1}
	});
	setup_pixel_rays();
	run_threads(data);
	mlx_key_hook(data->mlx, keyhook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	free_data();
	return (0);
}
