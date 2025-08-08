/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:53:37 by jvarila           #+#    #+#             */
/*   Updated: 2025/08/08 15:32:51 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	*raycasting_routine(void *arg);
static void	gradually_render(t_data *data, size_t i0, size_t precision);
static void	cast_ray(t_data *data, size_t i, size_t precision);

/**
 * TODO: Write documentation
 */
bool	run_threads(void)
{
	size_t	i;

	i = -1;
	pthread_mutex_lock(&g_data.lock);
	while (++i < THREADS)
	{
		if (pthread_create(&g_data.threads[i], NULL,
				&raycasting_routine, (void *)&g_data) != 0)
		{
			pthread_mutex_unlock(&g_data.lock);
			while (i--)
				pthread_join(g_data.threads[i], NULL);
			return (print_err("A thread failed to create"));
		}
	}
	pthread_mutex_unlock(&g_data.lock);
	return (true);
}

/**
 * TODO: Write documentation
 */
static void	*raycasting_routine(void *arg)
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
	while (!data->stop)
	{
		gradually_render(data, i0, precision);
		while (!data->stop && !data->work_to_be_done)
			usleep(10 * TICK);
	}
	return (NULL);
}

/**
 * TODO: Write documentation
 */
static void	gradually_render(t_data *data, size_t i0, size_t precision)
{
	size_t	i;

	++data->active_threads;
	while (precision > 0 && !data->stop && !data->pause)
	{
		i = i0 * precision;
		while (i < data->pixel_count && !data->stop && !data->pause)
		{
			cast_ray(data, i, precision);
			i += THREADS * precision;
		}
		precision /= 2;
		++data->threads_waiting;
		while (!(data->threads_waiting == THREADS || data->stop || data->pause))
			usleep(TICK);
		if (data->pause == true)
			--data->threads_waiting;
		if (data->stop || data->pause)
			break ;
		usleep(THREADS * TICK + 10);
		--data->threads_waiting;
	}
	--data->active_threads;
}

/**
 * TODO: Write documentation
 */
static void	cast_ray(t_data *data, size_t i, size_t precision)
{
	t_ray *const	ray = &data->pixel_rays[i];
	t_ray_x_obj		*rxo;
	t_phong_helper	p;
	t_flt_color	col;

	p = (t_phong_helper){};
	empty_intersections(ray);
	cast_ray_at_objs(ray, &data->elems, NULL);
	rxo = closest_rxo(&ray->intersections);
	if (rxo == NULL)
		col = get_sky_color(*ray, i);
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
		set_pixel_color(i++, color_flt_to_8bit(col));
}
