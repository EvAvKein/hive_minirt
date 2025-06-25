/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:52:22 by ekeinan           #+#    #+#             */
/*   Updated: 2025/06/25 17:02:44 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

static t_flt	to_radians(t_flt degrees)
{
	return (degrees * RADIANS_PER_DEGREE);
}

static t_flt	to_degrees(t_flt radians)
{
	return (radians * DEGREES_PER_RADIAN);
}

static t_float_color	lerp_color(t_float_color c1, t_float_color c2,
								float amount)
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

static t_8bit_color	color_float_to_8bit(t_float_color c)
{
	t_8bit_color	d;

	d.channel.r = 0xff * c.r;
	d.channel.g = 0xff * c.g;
	d.channel.b = 0xff * c.b;
	d.channel.a = 0xff * c.a;
	return (d);
}

static t_float_color	color_8bit_to_float(t_8bit_color c)
{
	t_float_color	d;

	d.r = c.channel.r / 255.0f;
	d.g = c.channel.g / 255.0f;
	d.b = c.channel.b / 255.0f;
	d.a = c.channel.a / 255.0f;
	return (d);
}

static void	set_horizontal_gradient(uint8_t *dest, size_t width, size_t height,
								t_float_color colors[2])
{
	t_float_color	between_flt;
	t_8bit_color	between_8bit;
	size_t			pixel_count;
	size_t			i;
	t_flt			zero_to_one_horizontal;

	if ((width && height > SIZE_MAX / width)
		|| (height && width > SIZE_MAX / height))
	{
		write(STDERR_FILENO, "set_uv: pixel count is over SIZE_MAX\n", 37);
		return ;
	}
	pixel_count = width * height;
	i = -1;
	while (++i < pixel_count)
	{
		zero_to_one_horizontal = (t_flt)(i % WINDOW_WIDTH) / WINDOW_WIDTH;
		between_flt = lerp_color(colors[0], colors[1], zero_to_one_horizontal);
		between_8bit = color_float_to_8bit(between_flt);
		ft_memcpy(dest + i * 4, &between_8bit.rgba, sizeof(uint32_t));
	}
}

static void	set_vertical_gradient(uint8_t *dest, size_t width, size_t height,
								t_float_color colors[2])
{
	t_float_color	between_flt;
	t_8bit_color	between_8bit;
	size_t			pixel_count;
	size_t			i;
	t_flt			zero_to_one_vertical;

	if ((width && height > SIZE_MAX / width)
		|| (height && width > SIZE_MAX / height))
	{
		write(STDERR_FILENO, "set_uv: pixel count is over SIZE_MAX\n", 37);
		return ;
	}
	pixel_count = width * height;
	i = -1;
	while (++i < pixel_count)
	{
		zero_to_one_vertical = (t_flt)(i / WINDOW_WIDTH) / WINDOW_WIDTH;
		between_flt = lerp_color(colors[0], colors[1], zero_to_one_vertical);
		between_8bit = color_float_to_8bit(between_flt);
		ft_memcpy(dest + i * 4, &between_8bit.rgba, sizeof(uint32_t));
	}
}

static void	set_uv(uint8_t *dest, size_t width, size_t height)
{
	t_8bit_color	color;
	size_t			pixel_count;
	size_t			i;
	t_flt			zero_to_one_horizontal;
	t_flt			zero_to_one_vertical;

	if ((width && height > SIZE_MAX / width)
		|| (height && width > SIZE_MAX / height))
	{
		write(STDERR_FILENO, "set_uv: pixel count is over SIZE_MAX\n", 37);
		return ;
	}
	pixel_count = width * height;
	i = -1;
	while (++i < pixel_count)
	{
		color.channel.a = 0xff;
		color.channel.b = 0;
		zero_to_one_horizontal = (t_flt)(i % WINDOW_WIDTH) / WINDOW_WIDTH;
		zero_to_one_vertical = (t_flt)(i / WINDOW_WIDTH) / WINDOW_HEIGHT;
		color.channel.g = (uint8_t)(zero_to_one_vertical * 0xff);
		color.channel.r = (uint8_t)(zero_to_one_horizontal * 0xff);
		ft_memcpy(dest + i * 4, &color.rgba, sizeof(uint32_t));
	}
}

/**
 * 
 * @returns A pointer to the program's data.
 * 
 */
t_data	*get_data(void)
{
	static t_data	minirt;

	return (&minirt);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		print_err("program must be provided a single argument");
		return (1);
	}
	if (!parse_scene(argv[1]))
	{
		free_data();
		return (1);
	}
	free_data();
	return (0);
}
