/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_initialization.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:27:40 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/11 16:06:14 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	init_sphere_transform(void);
static void	init_plane_transform(void);
static void	init_cylinder_transform(void);
static void	init_camera_transform(void);

void	init_transforms(void)
{
	init_camera_transform();
	init_sphere_transform();
	init_plane_transform();
	init_cylinder_transform();
}

static void	init_camera_transform(void)
{
	t_camera	*cam;
	t_flt		pitch_angle;
	t_flt		yaw_angle;

	cam = get_data()->elems.camera;
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

static void	init_sphere_transform(void)
{
	t_sphere	*sp;

	sp = get_data()->elems.spheres;
	while (sp)
	{
		sp->transform = translation_m4x4(sp->pos);
		sp->inverse = inverse_m4x4(sp->transform);
		sp = sp->next;
	}
}

static void	init_plane_transform(void)
{
	t_plane	*pl;
	t_flt	pitch_angle;
	t_flt	yaw_angle;

	pl = get_data()->elems.planes;
	while (pl)
	{
		if (vecs_are_equal(pl->orientation, (t_vec4){0}))
			pl->orientation = (t_vec4){.axis.y = 1};
		pl->orientation = unit_vec(pl->orientation);
		pitch_angle = atan(pl->orientation.axis.z / pl->orientation.axis.y);
		yaw_angle = atan(pl->orientation.axis.x / pl->orientation.axis.z);
		pl->transform = x_rotation_m4x4(pitch_angle);
		pl->transform = mult_m4x4(y_rotation_m4x4(yaw_angle), pl->transform);
		pl->transform = mult_m4x4(translation_m4x4(pl->pos), pl->transform);
		pl->inverse = inverse_m4x4(pl->transform);
		pl = pl->next;
	}
}

static void	init_cylinder_transform(void)
{
	t_cylinder	*cyl;
	t_flt		pitch_angle;
	t_flt		yaw_angle;

	cyl = get_data()->elems.cylinders;
	while (cyl)
	{
		if (vecs_are_equal(cyl->orientation, (t_vec4){0}))
			cyl->orientation = (t_vec4){.axis.y = 1};
		cyl->orientation = unit_vec(cyl->orientation);
		pitch_angle = atan(cyl->orientation.axis.z);
		yaw_angle = atan(cyl->orientation.axis.x / cyl->orientation.axis.z);
		cyl->transform = x_rotation_m4x4(pitch_angle);
		cyl->transform = mult_m4x4(y_rotation_m4x4(yaw_angle), cyl->transform);
		cyl->transform = mult_m4x4(translation_m4x4(cyl->pos), cyl->transform);
		cyl->inverse = inverse_m4x4(cyl->transform);
		cyl = cyl->next;
	}
}
