/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_initialization.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:27:40 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/16 18:40:11 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Runs transform initialization functions for elements in data.
 */
void	init_transforms(void)
{
	t_data *const	data = get_data();
	t_camera *const	cam = data->elems.camera;
	t_sphere		*sp;
	t_plane			*pl;
	t_cylinder		*cyl;

	sp = data->elems.spheres;
	pl = data->elems.planes;
	cyl = data->elems.cylinders;
	init_camera_transform(cam);
	while (sp)
	{
		init_sphere_transform(sp);
		sp = sp->next;
	}
	while (pl)
	{
		init_plane_transform(pl);
		pl = pl->next;
	}
	while (cyl)
	{
		init_cylinder_transform(cyl);
		cyl = cyl->next;
	}
}

/**
 * Initializes camera's transform and inverse using the parsed orientation
 * and position.
 */
void	init_camera_transform(t_camera *cam)
{
	t_flt		pitch_angle;
	t_flt		yaw_angle;

	if (vecs_are_equal(cam->orientation, (t_vec4){0}))
		cam->orientation = (t_vec4){.axis.z = 1};
	cam->orientation = unit_vec(cam->orientation);
	pitch_angle = atan(cam->orientation.axis.y / cam->orientation.axis.z);
	yaw_angle = atan(cam->orientation.axis.x / cam->orientation.axis.z);
	cam->transform = x_rotation_m4x4(-pitch_angle);
	cam->transform = mult_m4x4(y_rotation_m4x4(yaw_angle), cam->transform);
	cam->transform = mult_m4x4(translation_m4x4(cam->pos), cam->transform);
	cam->inverse = inverse_m4x4(cam->transform);
}

/**
 * Initializes sphere's transform and inverse using the parsed position.
 */
void	init_sphere_transform(t_sphere *sp)
{
	sp->transform = translation_m4x4(sp->pos);
	sp->inverse = inverse_m4x4(sp->transform);
}

/**
 * Initializes plane's transform and inverse using the parsed orientation
 * and position.
 */
void	init_plane_transform(t_plane *pl)
{
	t_flt	pitch_angle;
	t_flt	yaw_angle;

	if (vecs_are_equal(pl->orientation, (t_vec4){0}))
		pl->orientation = (t_vec4){.axis.y = 1};
	pl->orientation = unit_vec(pl->orientation);
	pitch_angle = atan(pl->orientation.axis.z / pl->orientation.axis.y);
	yaw_angle = atan(pl->orientation.axis.x / pl->orientation.axis.z);
	pl->transform = x_rotation_m4x4(pitch_angle);
	pl->transform = mult_m4x4(y_rotation_m4x4(yaw_angle), pl->transform);
	pl->transform = mult_m4x4(translation_m4x4(pl->pos), pl->transform);
	pl->inverse = inverse_m4x4(pl->transform);
}

/**
 * Initializes cylinder's transform and inverse using the parsed orientation
 * and position.
 */
void	init_cylinder_transform(t_cylinder *cyl)
{
	t_flt		pitch_angle;
	t_flt		yaw_angle;

	if (vecs_are_equal(cyl->orientation, (t_vec4){0}))
		cyl->orientation = (t_vec4){.axis.y = 1};
	cyl->orientation = unit_vec(cyl->orientation);
	pitch_angle = atan(cyl->orientation.axis.z / cyl->orientation.axis.y);
	yaw_angle = atan(cyl->orientation.axis.x / cyl->orientation.axis.z);
	cyl->transform = x_rotation_m4x4(pitch_angle);
	cyl->transform = mult_m4x4(y_rotation_m4x4(yaw_angle), cyl->transform);
	cyl->transform = mult_m4x4(translation_m4x4(cyl->pos), cyl->transform);
	cyl->inverse = inverse_m4x4(cyl->transform);
}
