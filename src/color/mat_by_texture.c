/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_by_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:12:24 by ekeinan           #+#    #+#             */
/*   Updated: 2025/08/07 21:28:59 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @param uv_pos	The UV-mapped coordinates of the position
 *					for which to return a material based on the image.
 *
 * @param image		The image in which to use the color from the provided UV
 *
 * @returns	A material with the color of the pixel
 *			at the provided UV position in the provided image
 */
t_material	mat_by_texture(t_vec4 uv_pos, mlx_image_t *image)
{
	size_t			x_idx;
	size_t			y_start_idx;
	size_t			final_idx;
	t_8bit_color	color;

	x_idx = round(uv_pos.x * image->width);
	y_start_idx = round(uv_pos.y * image->height);
	final_idx = (y_start_idx * image->width) + x_idx;
	if (final_idx > image->width * image->height)
		final_idx %= image->width * image->height;
	color = get_pixel_color(image, final_idx);
	return (pattern_mat_with_color(SOLID, color_8bit_to_flt(color)));
}

/**
 * @param relative_pos	A hit point (in object space) on the provided sphere
 *
 * @param sp			The sphere being hit
 *
 * @returns	A material with the color
 *			at the provided position based on the sphere's image.
 */
inline t_material	mat_by_texture_sphere(
						t_vec4 relative_pos, t_sphere *sp)
{
	return (mat_by_texture(
			point_to_uv(SPHERE, relative_pos, sp->radius * 2),
			sp->image));
}

/**
 * @param relative_pos	A hit point (in object space) on the provided plane
 *
 * @param sp			The plane being hit
 *
 * @returns	A material with the color
 *			at the provided position based on the plane's image.
 */
inline t_material	mat_by_texture_plane(
						t_vec4 relative_pos, t_plane *pl)
{
	return (mat_by_texture(
			point_to_uv(PLANE, relative_pos, -1),
			pl->image));
}

/**
 * @param relative_pos	A hit point (in object space) on the provided cylinder
 *
 * @param sp			The cylinder being hit
 *
 * @returns	A material with the color
 *			at the provided position based on the cylinder's image.
 */
inline t_material	mat_by_texture_cylinder(
						t_vec4 relative_pos, t_cylinder *cyl)
{
	return (mat_by_texture(
			point_to_uv(CYLINDER, relative_pos, cyl->height),
			cyl->image));
}

/**
 * @param relative_pos	A hit point (in object space) on the provided cone
 *
 * @param sp			The cone being hit
 *
 * @returns	A material with the color
 *			at the provided position based on the cone's image.
 */
inline t_material	mat_by_texture_cone(
						t_vec4 relative_pos, t_cone *cn)
{
	return (mat_by_texture(
			point_to_uv(CONE, relative_pos, cn->height),
			cn->image));
}
