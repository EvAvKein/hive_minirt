/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_initialization.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 09:52:46 by jvarila           #+#    #+#             */
/*   Updated: 2025/08/13 09:56:20 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_cones(t_cone *cn)
{
	while (cn)
	{
		cn->initial_pos = cn->pos;
		cn->initial_orientation = cn->orientation;
		init_cone_transform(cn);
		cn->material = default_material();
		cn->material.color = point(cn->color.r, cn->color.g, cn->color.b);
		cn = cn->next;
	}
}
