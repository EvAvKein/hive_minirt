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
 * Converts a vec4 containing the normal of a surface into the corresponding
 * 8 bit color.
 *
 * @param normal	Normal vector to convert into a color
 *
 * @returns Color that corrensponds to vec4 parameter normal
 */
t_8bit_color	normal_to_color(t_vec4 normal)
{
	t_8bit_color	col;

	col.r = (normal.x * 0.5 + 0.5) * 255.999;
	col.g = (normal.y * 0.5 + 0.5) * 255.999;
	col.b = (-normal.z * 0.5 + 0.5) * 255.999;
	col.a = 0xff;
	return (col);
}
