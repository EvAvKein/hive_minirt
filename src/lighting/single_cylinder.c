/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:13:35 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/16 17:28:02 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	single_cylinder_test(void)
{
	t_cylinder	cyl;

	cyl.pos = position(0, 0, 20);
	cyl.diam = 10;
	cyl.orientation = vector(0, 1, 0);
}
