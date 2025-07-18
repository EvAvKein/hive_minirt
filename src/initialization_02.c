/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization_02.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:11:29 by ekeinan           #+#    #+#             */
/*   Updated: 2025/07/16 10:32:09 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	init_lights(t_light *light);
static void	init_spheres(t_sphere *sp);
static void	init_planes(t_plane *pl);
static void	init_cylinders(t_cylinder *cyl);

void	init_object_data(void)
{
	t_data *const	data = get_data();

	init_lights(data->elems.lights);
	init_spheres(data->elems.spheres);
	init_planes(data->elems.planes);
	init_cylinders(data->elems.cylinders);
	init_camera_transform(data->elems.camera);
}

static void	init_lights(t_light *light)
{
	while (light)
	{
		light->transform = identity_m4x4();
		light->color.flt = color_8bit_to_float(light->color.bit);
		light = light->next;
	}
}

static void	init_spheres(t_sphere *sp)
{
	while (sp)
	{
		sp->transform = translation_m4x4(sp->pos);
		sp->inverse = inverse_m4x4(sp->transform);
		sp->material = default_material();
		sp = sp->next;
	}
}

static void	init_planes(t_plane *pl)
{
	t_flt	pitch_angle;
	t_flt	yaw_angle;

	while (pl)
	{
		if (vecs_are_equal(pl->orientation, (t_vec4){0}))
			pl->orientation = (t_vec4){.axis.y = 1};
		pitch_angle = 0;
		yaw_angle = 0;
		pl->orientation = unit_vec(pl->orientation);
		if (!floats_are_equal(pl->orientation.axis.y, 0))
			pitch_angle = atan(pl->orientation.axis.z / pl->orientation.axis.y);
		if (!floats_are_equal(pl->orientation.axis.z, 0))
			yaw_angle = atan(pl->orientation.axis.x / pl->orientation.axis.z);
		pl->transform = x_rotation_m4x4(pitch_angle);
		pl->transform = mult_m4x4(y_rotation_m4x4(yaw_angle), pl->transform);
		pl->transform = mult_m4x4(translation_m4x4(pl->pos), pl->transform);
		pl->inverse = inverse_m4x4(pl->transform);
		pl->material = default_material();
		pl = pl->next;
	}
}

static void	init_cylinders(t_cylinder *cyl)
{
	t_flt		pitch_angle;
	t_flt		yaw_angle;

	while (cyl)
	{
		if (vecs_are_equal(cyl->orientation, (t_vec4){0}))
			cyl->orientation = (t_vec4){.axis.y = 1};
		pitch_angle = 0;
		yaw_angle = 0;
		cyl->orientation = unit_vec(cyl->orientation);
		if (!floats_are_equal(cyl->orientation.axis.y, 0))
			pitch_angle = atan(cyl->orientation.axis.z
					/ cyl->orientation.axis.y);
		if (!floats_are_equal(cyl->orientation.axis.z, 0))
			yaw_angle = atan(cyl->orientation.axis.x / cyl->orientation.axis.z);
		cyl->transform = x_rotation_m4x4(pitch_angle);
		cyl->transform = mult_m4x4(y_rotation_m4x4(yaw_angle), cyl->transform);
		cyl->transform = mult_m4x4(translation_m4x4(cyl->pos), cyl->transform);
		cyl->inverse = inverse_m4x4(cyl->transform);
		cyl->material = default_material();
		cyl = cyl->next;
	}
}
