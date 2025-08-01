/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_mapping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:17:26 by ekeinan           #+#    #+#             */
/*   Updated: 2025/07/30 11:50:17 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * TODO: Write these docs
 */
static size_t	pixel_i_with_wrap(mlx_image_t *map,
					size_t pixel_x, size_t pixel_y)
{
	if (pixel_x >= map->width)
		pixel_x %= map->width;
	if (pixel_y >= map->height)
		pixel_y %= map->height;
	return (pixel_y * map->width + pixel_x);
}

/**
 * TODO: Write these docs
 */
t_flt	color_adjust_by_bump_map(t_vec4 uv_point, mlx_image_t *map)
{
	t_vec2	pixel;
	t_vec4	color;
	t_flt	adjustment;
 
	pixel.x = round((t_flt)map->width * uv_point.x);
	pixel.y = round((t_flt)map->height * uv_point.y);
	color = get_pixel_color(
				pixel_i_with_wrap(map, pixel.x + 1, pixel.y));
	color = vec_sum(color, get_pixel_color(
								pixel_i_with_wrap(map, pixel.x - 1, pixel.y)));
	color = vec_sum(color, get_pixel_color(
								pixel_i_with_wrap(map, pixel.x, pixel.y + 1)));
	color = vec_sum(color, get_pixel_color(
								pixel_i_with_wrap(map, pixel.x, pixel.y - 1)));
	color.r = color.r / 4 / 256;
	color.g = color.g / 4 / 256;
	color.b = color.b / 4 / 256;
	adjustment = color.r + color.g + color.b;
	return (adjustment);
}
