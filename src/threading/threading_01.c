/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:53:37 by jvarila           #+#    #+#             */
/*   Updated: 2025/08/11 16:52:44 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	*raycasting_routine(void *arg);
static void	gradually_render(size_t i0, uint16_t precision);
static void	cast_rays(size_t i0, uint16_t precision);
static void	cast_ray(size_t i, uint16_t precision);

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
	pthread_mutex_lock(&dat()->lock);
	if (pthread_create(&dat()->monitor_thread, NULL,
			&monitor_thread, NULL) != 0)
		return (print_err("The monitor thread failed to create"));
	while (++i < THREADS)
	{
		if (pthread_create(&dat()->threads[i], NULL,
				&raycasting_routine, (void *)dat()) != 0)
		{
			pthread_mutex_unlock(&dat()->lock);
			while (i--)
				pthread_join(dat()->threads[i], NULL);
			pthread_join(dat()->monitor_thread, NULL);
			return (print_err("A rendering thread failed to create"));
		}
	}
	dat()->jobs_available = THREADS;
	pthread_mutex_unlock(&dat()->lock);
	return (true);
}

/**
 * The raycasting routine finds out the thread's number and runs the rendering
 * loop. The loop gradually renders with higher accuracy (the precision number
 * tells how many pixels get a copy of the same color sample, so the smaller
 * the precision the more accurate the render). Waits for events when done with
 * rendering.
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
		--dat()->jobs_available;
		gradually_render(i0, precision);
		while (!data->stop_threads
			&& (dat()->jobs_available == 0 || dat()->pause_threads))
			usleep(10 * TICK);
	}
	return (NULL);
}

/**
 * Controls how a thread casts rays in sync with the other threads.
 *
 * @param i0		Thread's index in range [0, THREADS - 1]
 * @param precision	Amount of pixels to color by one sample initially
 */
static void	gradually_render(size_t i0, uint16_t precision)
{
	++dat()->active_threads;
	while (!dat()->stop_threads && !dat()->pause_threads
		&& dat()->active_threads != THREADS)
		usleep(TICK);
	while (precision > 0 && !dat()->stop_threads && !dat()->pause_threads)
	{
		cast_rays(i0, precision);
		precision /= 2;
		++dat()->threads_waiting;
		while (!dat()->stop_threads && !dat()->pause_threads
			&& !dat()->thread_can_proceed[i0])
			usleep(TICK);
		dat()->thread_can_proceed[i0] = false;
		--dat()->threads_waiting;
		if (dat()->stop_threads || dat()->pause_threads)
			break ;
	}
	--dat()->active_threads;
}

/**
 * Loops through the assigned render regions of the thread, casting rays as
 * it goes. A thread renders precision pixels starting at its own index
 * times precision, then it moves forward by THREADS * precision to render
 * an unrendered region that no other thread is accessing.
 *
 * @param i0		Thread's index in range [0, THREADS - 1]
 * @param precision	Amount of pixels to color by one sample initially
 */
static void	cast_rays(size_t i0, uint16_t precision)
{
	size_t	i;

	i = i0 * precision;
	while (i < dat()->pixel_count
		&& !dat()->stop_threads && !dat()->pause_threads)
	{
		cast_ray(i, precision);
		i += THREADS * precision;
	}
}

/**
 * Casts a ray for pixel i and assigns the result color based on the color
 * sampled by that ray to precision amount of pixels.
 *
 * @param i			Index of pixel to sample for
 * @param precision	Pixels to color by ray sample result
 */
static void	cast_ray(size_t i, uint16_t precision)
{
	t_ray			ray;
	t_phong_helper	p;
	t_flt_color		col;

	ray = ray_for_pixel(i);
	p = (t_phong_helper){};
	cast_ray_at_objs(&ray, &dat()->elems, NULL);
	if (ray.closest_hit.t == MAX_DIST)
		col = get_sky_color(ray, i);
	else
	{
		p.light = dat()->elems.lights;
		p.ray = &ray;
		p.pos = ray_position(ray, ray.closest_hit.t);
		p.to_cam = opposite_vec(ray.dir);
		p.obj_hit = ray.closest_hit.obj;
		col = color_at_obj_hit(&ray.closest_hit, &p);
	}
	while (precision--)
		set_pixel_color(i++, color_flt_to_8bit(col));
}
