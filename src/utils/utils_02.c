/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:11:04 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/09 11:59:33 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

t_quad	solve_sphere_quadratic(t_ray ray, t_sphere sp)
{
	t_vec4	sp_to_ray;
	t_quad	q;

	sp_to_ray = vec_sub(ray.orig, sp.pos);
	q.a = dot(ray.dir, ray.dir);
	q.b = 2 * dot(ray.dir, sp_to_ray);
	q.c = dot(sp_to_ray, sp_to_ray) - sp.radius * sp.radius;
	q.discr = q.b * q.b - 4 * q.a * q.c;
	return (q);
}

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
