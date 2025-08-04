/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_01.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 21:22:10 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/17 10:54:12 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Sets the color at the provided pixel index to the provided color
 */
void	set_pixel_color(size_t pixel_i, t_color color)
{
	if (pixel_i < g_data.pixel_count)
	{
		g_data.img->pixels[pixel_i * 4 + 0] = color.bit.r;
		g_data.img->pixels[pixel_i * 4 + 1] = color.bit.g;
		g_data.img->pixels[pixel_i * 4 + 2] = color.bit.b;
		g_data.img->pixels[pixel_i * 4 + 3] = 0xff;
	}
}

/**
 * Convenience function for easily creating colors
 *
 * @returns	t_color struct with colors set to match c
 */
t_color	color_from_uint32(uint32_t c)
{
	t_color	col;

	col.bit.rgba = c;
	col.flt = color_8bit_to_flt(col.bit);
	return (col);
}

/**
 * @returns	Float color converted from 8 bit color c
 */
t_flt_color	color_8bit_to_flt(t_8bit_color c)
{
	t_flt_color	d;

	d.r = c.r / 255.0f;
	d.g = c.g / 255.0f;
	d.b = c.b / 255.0f;
	d.a = c.a / 255.0f;
	return (d);
}

/**
 * @returns	8 bit color converted from float color parameter c
 */
t_8bit_color	color_flt_to_8bit(t_flt_color c)
{
	t_8bit_color	d;

	d.r = fminf(fmaxf(0, 255.999 * c.r), 255.999);
	d.g = fminf(fmaxf(0, 255.999 * c.g), 255.999);
	d.b = fminf(fmaxf(0, 255.999 * c.b), 255.999);
	d.a = fminf(fmaxf(0, 255.999 * c.a), 255.999);
	return (d);
}

/**
 * @returns	Color that sits between c1 and c2, defined by the amount [0, 1]
 */
t_flt_color	lerp_color(t_flt_color c1, t_flt_color c2, float amount)
{
	t_flt_color	between;

	if (amount <= 0)
		return (c1);
	if (amount >= 1)
		return (c2);
	between.r = c1.r + (c2.r - c1.r) * amount;
	between.g = c1.g + (c2.g - c1.g) * amount;
	between.b = c1.b + (c2.b - c1.b) * amount;
	between.a = c1.a + (c2.a - c1.a) * amount;
	return (between);
}
