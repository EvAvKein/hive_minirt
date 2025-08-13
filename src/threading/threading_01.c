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

static void			*raycasting_routine(void *arg);
static void			gradually_render(size_t i0, size_t width);
static t_flt_color	sample_ray(size_t i);
static bool			thread_can_continue(void);

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
	size_t			idx[2];
	size_t			width;
	pthread_t		id;

	(void)arg;
	pthread_mutex_lock(&dat()->lock);
	pthread_mutex_unlock(&dat()->lock);
	id = pthread_self();
	idx[0] = 0;
	while (id != dat()->threads[idx[0]])
		++idx[0];
	while (!dat()->stop_threads)
	{
		width = dat()->pixel_count / THREADS;
		idx[1] = idx[0] * width;
		--dat()->jobs_available;
		gradually_render(idx[1], width);
		while (!dat()->stop_threads
			&& (dat()->jobs_available == 0 || dat()->pause_threads))
			usleep(10 * TICK);
	}
	return (NULL);
}

/**
 * Controls how a thread casts rays in sync with the other threads.
 *
 * @param i0		Starting index
 * @param precision	Amount of pixels to color by one sample initially
 */
static void	gradually_render(size_t i0, size_t width)
{
	t_8bit_color	col;
	size_t			precision;
	size_t			i;
	size_t			j;

	++dat()->active_threads;
	precision = dat()->img->width / (2 * THREADS);
	if (precision <= 0)
		precision = 2;
	while (thread_can_continue() && precision > 0)
	{
		precision /= 2;
		i = 0;
		while (thread_can_continue() && i < width)
		{
			col = color_flt_to_8bit(sample_ray(i0 + i));
			j = -1;
			while (thread_can_continue() && ++j < precision)
				set_pixel_color(i0 + i + j, col);
			i += precision;
		}
	}
	--dat()->active_threads;
}

/**
 * Casts a ray for pixel i and assigns the result color based on the color
 * sampled by that ray to precision amount of pixels.
 *
 * @param i			Index of pixel to sample for
 * @param precision	Pixels to color by ray sample result
 */
static t_flt_color	sample_ray(size_t i)
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
	return (col);
}

static inline bool	thread_can_continue(void)
{
	return (!dat()->stop_threads && !dat()->pause_threads);
}
