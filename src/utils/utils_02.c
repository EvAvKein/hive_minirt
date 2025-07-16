/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:11:04 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/16 13:08:07 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Used this function for debugging raycasting.
 *
 * TODO: Remove function before eval or move to a debug source file
 */
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
		print_vec(data->pixel_rays[i].dir);
	fflush(stdout);
	close(fds[0]);
	dup2(fds[1], STDOUT_FILENO);
	close(fds[1]);
}

/**
 * Helper function for converting a vec4 into a color object.
 *
 * @returns	Color based on vec4 parameter vec, with the following mapping:
 *			r = x
 *			g = y
 *			b = z
 *			a = w
 */
t_color	vec4_to_color(t_vec4 vec)
{
	t_color	col;

	col.flt.r = vec.axis.x;
	col.flt.g = vec.axis.y;
	col.flt.b = vec.axis.z;
	col.flt.a = vec.axis.w;
	col.bit = color_float_to_8bit(col.flt);
	return (col);
}

/**
 * Converts a vec4 containing the normal of a surface into the corresponding
 * color.
 *
 * @returns Color that corrensponds to vec4 parameter normal
 */
t_color	normal_to_color(t_vec4 normal)
{
	t_color	col;

	col.bit.channel.r = (normal._[0] * 0.5 + 0.5) * 255.999 * 1;
	col.bit.channel.g = (normal._[1] * 0.5 + 0.5) * 255.999 * 1;
	col.bit.channel.b = (-normal._[2] * 0.5 + 0.5) * 255.999 * 1;
	col.bit.channel.a = 0xff;
	col.flt = color_8bit_to_float(col.bit);
	return (col);
}

/**
 * @returns	Attempts to calloc, frees data and exits program if calloc fails.
 *			Returns void pointer to allocated memory block.
 */
void	*xcalloc(size_t nmemb, size_t size)
{
	void	*mem;

	mem = ft_calloc(nmemb, size);
	if (mem == NULL)
	{
		ft_putendl_fd("ERROR: xcalloc: couldn't allocate memory",
			STDERR_FILENO);
		free_data();
		exit(ERROR_ALLOC);
	}
	return (mem);
}

/**
 * @returns	Struct containing the smallest non-negative t-valued intersection
 *			in rxos (ray-object intersections), 0 struct when both t-values
 *			are negative
 */
t_ray_x_obj	hit(t_ray_x_objs rxos)
{
	if (rxos._[0].t < 0 && rxos._[1].t < 0)
		return ((t_ray_x_obj){0});
	if (rxos._[0].t < 0)
		return (rxos._[1]);
	if (rxos._[1].t > 0
		&& rxos._[0].t > rxos._[1].t)
		return (rxos._[1]);
	return (rxos._[0]);
}
