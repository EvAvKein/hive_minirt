/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:13:51 by ekeinan           #+#    #+#             */
/*   Updated: 2025/07/29 17:23:39 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Gets the color at the provided pixel index
 */
t_vec4	get_pixel_color(size_t pixel_i)
{
	t_data *const	data = get_data();
	t_vec4			color;
	const size_t	pixel_start_i = pixel_i * 4;

	color.x = (t_flt)data->img->pixels[pixel_start_i + 0] / 256;
	color.y = (t_flt)data->img->pixels[pixel_start_i + 1] / 256;
	color.z = (t_flt)data->img->pixels[pixel_start_i + 2] / 256;
	color.w = (t_flt)data->img->pixels[pixel_start_i + 3] / 256;
	return (color);
}
