/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:11:04 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/22 12:57:00 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Used this function for debugging raycasting.
 *
 * @param str	String containing file name to write data into
 *
 * TODO: Remove function before eval or move to a debug source file
 */
void	write_pixel_rays_to_file(const char *str)
{
	size_t	i;
	t_data	*data;
	int		fds[2];

	fds[0] = open(str, O_CREAT | O_TRUNC | O_WRONLY, 0666);
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
 * @param vec	Vec4 to convert into a color
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

	col.flt.r = vec.x;
	col.flt.g = vec.y;
	col.flt.b = vec.z;
	col.flt.a = vec.w;
	col.bit = color_float_to_8bit(col.flt);
	return (col);
}

/**
 * Helper function for converting an 8-bit color object into a vec4.
 * Converts the 8-bit values to float colors first using a different helper.
 *
 * @param color_8bit	8-bit color to convert into a vec4
 *
 * @returns	Vec4 based on the 8-bit color parameter, with the following mapping:
 *			r = x
 *			g = y
 *			b = z
 *			a = w
 */
t_vec4	color_8bit_to_vec4(t_8bit_color color_8bit)
{
	const t_float_color	color_float = color_8bit_to_float(color_8bit);
	t_vec4				vec;

	vec.x = color_float.r;
	vec.y = color_float.g;
	vec.z = color_float.b;
	vec.w = color_float.a;
	return (vec);
}

/**
 * Converts a vec4 containing the normal of a surface into the corresponding
 * color.
 *
 * @param normal	Normal vector to convert into a color
 *
 * @returns Color that corrensponds to vec4 parameter normal
 */
t_color	normal_to_color(t_vec4 normal)
{
	t_color	col;

	col.bit.r = (normal.x * 0.5 + 0.5) * 255.999 * 1;
	col.bit.g = (normal.y * 0.5 + 0.5) * 255.999 * 1;
	col.bit.b = (-normal.z * 0.5 + 0.5) * 255.999 * 1;
	col.bit.a = 0xff;
	col.flt = color_8bit_to_float(col.bit);
	return (col);
}

/**
 * Attempts to calloc, frees data and exits program if calloc fails.
 *
 * @param nmemb	Number of members to allocate
 * @param size	Size of members to allocate
 *
 * @returns	Void pointer to allocated memory block
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
