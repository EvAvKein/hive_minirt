/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_01.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 21:22:10 by jvarila           #+#    #+#             */
/*   Updated: 2025/06/25 23:30:31 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @returns	Float color converted from 8 bit color c
 */
t_float_color	color_8bit_to_float(t_8bit_color c)
{
	t_float_color	d;

	d.r = c.channel.r / 255.0f;
	d.g = c.channel.g / 255.0f;
	d.b = c.channel.b / 255.0f;
	d.a = c.channel.a / 255.0f;
	return (d);
}

/**
 * @returns	8 bit color converted from float color parameter c
 */
t_8bit_color	color_float_to_8bit(t_float_color c)
{
	t_8bit_color	d;

	d.channel.r = 0xff * c.r;
	d.channel.g = 0xff * c.g;
	d.channel.b = 0xff * c.b;
	d.channel.a = 0xff * c.a;
	return (d);
}

/**
 * @returns	Color that sits between c1 and c2, defined by the amount [0, 1]
 */
t_float_color	lerp_color(t_float_color c1, t_float_color c2, float amount)
{
	t_float_color	between;

	if (amount < 0)
		return (c1);
	if (amount > 1)
		return (c2);
	between.r = c1.r + (c2.r - c1.r) * amount;
	between.g = c1.g + (c2.g - c1.g) * amount;
	between.b = c1.b + (c2.b - c1.b) * amount;
	between.a = c1.a + (c2.a - c1.a) * amount;
	return (between);
}
