/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backgrounds_01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 21:53:24 by jvarila           #+#    #+#             */
/*   Updated: 2025/08/08 16:24:39 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_8bit_color	get_image_pixel_color(mlx_image_t const *img, size_t idx);

/**
 * TODO: Remove unused func?
 *
 * Sets pixel buffer to horizontal gradient, defined by the colors in the colors
 * array.
 *
 * @param img		Pointer to mlx image
 * @param colors	Array of two float colors
 */
void	set_horizontal_gradient(mlx_image_t *img, t_flt_color colors[2])
{
	t_8bit_color	between_8bit;
	size_t			pixel_count;
	size_t			i;
	t_flt			zero_to_one_horizontal;

	pixel_count = img->width * img->height;
	i = -1;
	while (++i < pixel_count)
	{
		zero_to_one_horizontal = (t_flt)(i % RES_X) / RES_X;
		between_8bit = color_flt_to_8bit(
				lerp_color(colors[0], colors[1], zero_to_one_horizontal));
		img->pixels[i * 4 + 0] = between_8bit.r;
		img->pixels[i * 4 + 1] = between_8bit.g;
		img->pixels[i * 4 + 2] = between_8bit.b;
		img->pixels[i * 4 + 3] = 0xff;
	}
}

/**
 * TODO: Remove unused func?
 *
 * Sets pixel buffer to vertical gradient, defined by the colors in the colors
 * array.
 *
 * @param img		Pointer to mlx image
 * @param colors	Array of two float colors
 */
void	set_vertical_gradient(mlx_image_t *img, t_flt_color colors[2])
{
	t_8bit_color	color;
	size_t			pixel_count;
	size_t			i;
	t_flt			zero_to_one_vertical;

	pixel_count = img->width * img->height;
	i = -1;
	while (++i < pixel_count)
	{
		zero_to_one_vertical = (t_flt)(i / img->width) / img->height;
		color = color_flt_to_8bit(
				lerp_color(colors[0], colors[1], zero_to_one_vertical));
		img->pixels[i * 4 + 0] = color.r;
		img->pixels[i * 4 + 1] = color.g;
		img->pixels[i * 4 + 2] = color.b;
		img->pixels[i * 4 + 3] = 0xff;
	}
}

/**
 * TODO: Remove unused func?
 *
 * Sets pixel buffer to uv coordinates (view space).
 *
 * @param img	Pointer to mlx image
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
		img->pixels[i * 4 + 0] = color.r;
		img->pixels[i * 4 + 1] = color.g;
		img->pixels[i * 4 + 2] = color.b;
		img->pixels[i * 4 + 3] = 0xff;
	}
}

/**
 * Calculates and returns color for sky pixels. If there is a sky 360 panorama
 * present it maps it to the sky, otherwise a default vertical screen space
 * gradient is used.
 *
 * @param ray	Ray being cast
 * @param i		Index of ray being cast
 *
 * @returns	Color of sky pixel
 */
t_flt_color	get_sky_color(t_ray ray, size_t i)
{
	t_vec2				uv;
	size_t				idx[3];
	static t_flt_color	sky_colors[2];
	t_flt_color			color;

	sky_colors[0] = (t_flt_color){.r = .1, .g = .8, .b = 1, .a = 1};
	sky_colors[1] = (t_flt_color){.r = 1, .g = 1, .b = 1, .a = 1};
	uv.x = 0.5 - atan2(ray.dir.z, ray.dir.x) / (2 * M_PI);
	uv.y = 0.5 - asin(ray.dir.y) / M_PI;
	if (!dat()->sky_image)
	{
		uv.y = (t_flt)(i / dat()->img->width) / dat()->img->height;
		color = lerp_color(sky_colors[0], sky_colors[1], uv.y);
		return (color);
	}
	idx[1] = round(uv.x * dat()->sky_image->width);
	idx[2] = round(uv.y * dat()->sky_image->height);
	idx[0] = dat()->sky_image->width * idx[2] + idx[1];
	return (color_8bit_to_flt(get_image_pixel_color(dat()->sky_image, idx[0])));
}

/**
 * Helper function for retrieving the color of a specific pixel in an image.
 *
 * @param img	Pointer to mlx image
 * @param idx	Index of pixel
 *
 * @returns	Color of pixel at index idx
 */
static t_8bit_color	get_image_pixel_color(mlx_image_t const *img, size_t idx)
{
	t_8bit_color	color;

	color.r = img->pixels[4 * idx + 0];
	color.g = img->pixels[4 * idx + 1];
	color.b = img->pixels[4 * idx + 2];
	color.a = 0xff;
	return (color);
}
