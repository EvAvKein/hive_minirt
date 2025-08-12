/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_at_cone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 15:34:18 by jvarila           #+#    #+#             */
/*   Updated: 2025/08/12 15:38:45 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	cast_ray_at_cones(t_ray *ray, t_cone *cones, void const *obj_ignore)
{
	t_ray_x_obj	rxo;
	t_cone		*cn;

	cn = cones;
	while (cn)
	{
		if (cn == obj_ignore)
		{
			cn = cn->next;
			continue ;
		}
		rxo = ray_hit_cone(*ray, cn);
		if (rxo.t > EPSILON && rxo.t < ray->closest_hit.t)
			ray->closest_hit = rxo;
		cn = cn->next;
	}
}
