/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:53:37 by jvarila           #+#    #+#             */
/*   Updated: 2025/08/08 15:09:06 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	*raycasting_routine(void *arg);
static void	gradually_render(size_t i0, uint16_t precision);
static void	cast_rays(size_t i0, uint16_t precision);
static void	cast_ray(t_data *data, size_t i, uint16_t precision);

/**
 * Creates threads, sets up initial jobs available to THREADS. Threads can't
 * start their routine until all threads are created. In case of an error cleans
 * up threads, prints an error and returns false.
 *
 * @returns	true when threads are succesfully created, false if not
 */
bool	run_threads(void)
{
	size_t	i;

	i = -1;
	pthread_mutex_lock(&g_data.lock);
	if (pthread_create(&g_data.monitor_thread, NULL,
			&monitor_thread, NULL) != 0)
		return (print_err("The monitor thread failed to create"));
	while (++i < THREADS)
	{
		if (pthread_create(&g_data.threads[i], NULL,
				&raycasting_routine, (void *)&g_data) != 0)
		{
			pthread_mutex_unlock(&g_data.lock);
			while (i--)
				pthread_join(g_data.threads[i], NULL);
			pthread_join(g_data.monitor_thread, NULL);
			return (print_err("A rendering thread failed to create"));
		}
	}
	g_data.jobs_available = THREADS;
	pthread_mutex_unlock(&g_data.lock);
	return (true);
}

/**
 * The raycasting routine finds out the thread's number and runs the rendering
 * loop. The loop gradually renders with higher accuracy (the precision number
 * tells how many pixels get a copy of the same color sample, so the smaller
 * the precision the more accurate the render).
 */
static void	*raycasting_routine(void *arg)
{
	t_data *const	data = arg;
	size_t			i0;
	pthread_t		id;
	uint16_t		precision;

	pthread_mutex_lock(&data->lock);
	pthread_mutex_unlock(&data->lock);
	id = pthread_self();
	i0 = 0;
	while (id != data->threads[i0])
		++i0;
	while (!data->stop_threads)
	{
		precision = STARTING_PRECISION;
		while ((precision >= data->img->width || precision >= data->img->height)
			&& precision >= 2)
			precision /= 2;
		--g_data.jobs_available;
		gradually_render(i0, precision);
		while (!data->stop_threads
			&& (g_data.jobs_available == 0 || g_data.pause_threads))
			usleep(10 * TICK);
	}
	return (NULL);
}

/**
 * Renders image in steps
 */
static void	gradually_render(size_t i0, uint16_t precision)
{
	++g_data.active_threads;
	while (!g_data.stop_threads && !g_data.pause_threads
		&& g_data.active_threads != THREADS)
		usleep(TICK);
	while (precision > 0 && !g_data.stop_threads && !g_data.pause_threads)
	{
		cast_rays(i0, precision);
		precision /= 2;
		++g_data.threads_waiting;
		while (!g_data.stop_threads && !g_data.pause_threads
			&& !g_data.thread_can_proceed[i0])
			usleep(TICK);
		g_data.thread_can_proceed[i0] = false;
		--g_data.threads_waiting;
		if (g_data.stop_threads || g_data.pause_threads)
			break ;
	}
	--g_data.active_threads;
}

/**
 * TODO: Write documentation
 */
static void	cast_rays(size_t i0, uint16_t precision)
{
	size_t	i;

	i = i0 * precision;
	while (i < g_data.pixel_count
		&& !g_data.stop_threads && !g_data.pause_threads)
	{
		cast_ray(&g_data, i, precision);
		i += THREADS * precision;
	}
}

/**
 * TODO: Write documentation
 */
static void	cast_ray(t_data *data, size_t i, uint16_t precision)
{
	t_ray			ray;
	t_phong_helper	p;
	t_color			col;

	ray = ray_for_pixel(i);
	p = (t_phong_helper){};
	cast_ray_at_objs(&ray, &data->elems, NULL);
	if (ray.closest_hit.t == MAX_DIST)
		col = get_sky_color(ray, i);
	else
	{
		p.light = data->elems.lights;
		p.ray = &ray;
		p.pos = ray_position(ray, ray.closest_hit.t);
		p.to_cam = opposite_vec(ray.dir);
		p.obj_hit = ray.closest_hit.obj;
		col = color_at_obj_hit(&ray.closest_hit, &p);
	}
	while (precision--)
		set_pixel_color(i++, col);
}
