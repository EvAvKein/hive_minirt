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
