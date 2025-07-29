/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backgrounds_01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 21:53:24 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/29 11:58:09 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Sets pixel buffer to horizontal gradient, defined by the colors in the colors
 * array.
 */
void	set_horizontal_gradient(mlx_image_t *img, t_flt_color colors[2])
{
	t_flt_color		between_flt;
	t_8bit_color	between_8bit;
	size_t			pixel_count;
	size_t			i;
	t_flt			zero_to_one_horizontal;

	pixel_count = img->width * img->height;
	i = -1;
	while (++i < pixel_count)
	{
		zero_to_one_horizontal = (t_flt)(i % RES_X) / RES_X;
		between_flt = lerp_color(colors[0], colors[1], zero_to_one_horizontal);
		between_8bit = color_float_to_8bit(between_flt);
		ft_memcpy(img->pixels + i * 4, &between_8bit.rgba, sizeof(uint32_t));
	}
}

/**
 * Sets pixel buffer to vertical gradient, defined by the colors in the colors
 * array.
 */
void	set_vertical_gradient(mlx_image_t *img, t_flt_color colors[2])
{
	t_color			col;
	size_t			pixel_count;
	size_t			i;
	t_flt			zero_to_one_vertical;

	pixel_count = img->width * img->height;
	i = -1;
	while (++i < pixel_count)
	{
		zero_to_one_vertical = (t_flt)(i / img->width) / img->height;
		col.flt = lerp_color(colors[0], colors[1], zero_to_one_vertical);
		col.bit = color_float_to_8bit(col.flt);
		ft_memcpy(img->pixels + i * 4, &col.bit.rgba, sizeof(uint32_t));
	}
}

/**
 * Sets pixel buffer to uv coordinates.
 */
void	set_uv(mlx_image_t *img)
{
	t_8bit_color	color;
	size_t			pixel_count;
	size_t			i;
	t_flt			zero_to_one_horizontal;
	t_flt			zero_to_one_vertical;

	pixel_count = img->width * img->height;
	color = (t_8bit_color){.a = 0xff, .b = 0};
	i = -1;
	while (++i < pixel_count)
	{
		zero_to_one_horizontal = (t_flt)(i % RES_X) / RES_X;
		zero_to_one_vertical = (t_flt)(i / RES_X) / RES_Y;
		color.g = (uint8_t)(zero_to_one_vertical * 0xff);
		color.r = (uint8_t)(zero_to_one_horizontal * 0xff);
		ft_memcpy(img->pixels + i * 4, &color.rgba, sizeof(uint32_t));
	}
}

t_color	get_sky_color(t_ray ray)
{
	t_vec2		uv;
	t_color		col;

	uv.x = 0.5 - atan2(ray.dir.z, ray.dir.x) / (2 * M_PI);
	uv.y = 0.5 - asin(ray.dir.y) / M_PI;
	col.flt = (t_flt_color){.r = uv.x, .g = uv.y, .a = 1};
	col.bit = color_float_to_8bit(col.flt);
	return (col);
}
