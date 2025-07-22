/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_initialization.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:27:40 by jvarila           #+#    #+#             */
/*   Updated: 2025/07/22 12:43:45 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Calculates pitch and yaw rotations for camera.
 *
 * @param cam	Camera struct pointer
 *
 * @returns	Float array containing the pitch and yaw angles
 */
static t_flt	*cam_pitch_and_yaw(t_camera *cam)
{
	static t_flt	angles[2];
	t_vec4			h;

	ft_bzero(angles, sizeof(t_flt) * 2);
	angles[0] = atan2(cam->orientation.y, vec_len(point(cam->orientation.x,
					0, cam->orientation.z)));
	h = unit_vec(vector(cam->orientation.x, 0, cam->orientation.z));
	angles[1] = atan2(h.x, h.z);
	return (angles);
}

/**
 * Calculates pitch and yaw rotations for a plane.
 *
 * @param cam	Plane struct
 *
 * @returns	Float array containing the pitch and yaw angles
 */
static t_flt	*plane_pitch_and_yaw(t_plane pl)
{
	static t_flt	angles[2];
	t_vec4			h;

	ft_bzero(angles, sizeof(t_flt) * 2);
	h = pl.orientation;
	angles[0] = atan2(vec_len(point(h.x, 0, h.z)), h.y);
	h = unit_vec(vector(pl.orientation.x, 0, pl.orientation.z));
	if (h.x < 0 && h.z >= 0)
		angles[1] = asin(-h.x);
	else if (h.x < 0 && h.z < 0)
		angles[1] = M_PI - asin(-h.x);
	else if (h.x >= 0 && h.z >= 0)
		angles[1] = -asin(h.x);
	else
		angles[1] = -M_PI + asin(h.x);
	return (angles);
}

/**
 * Calculates pitch and yaw rotations for camera.
 *
 * @param cam	Camera struct pointer
 *
 * @returns	Float array containing the pitch and yaw angles
 */
static t_flt	*cam_pitch_and_yaw(t_camera *cam)
{
	static t_flt	angles[2];
	t_vec4			h;

	ft_bzero(angles, sizeof(t_flt) * 2);
	angles[0] = atan2(cam->orientation.y, vec_len(point(cam->orientation.x,
					0, cam->orientation.z)));
	h = unit_vec(vector(cam->orientation.x, 0, cam->orientation.z));
	angles[1] = atan2(h.x, h.z);
	return (angles);
}

/**
 * Calculates pitch and yaw rotations for a plane.
 *
 * @param cam	Plane struct
 *
 * @returns	Float array containing the pitch and yaw angles
 */
static t_flt	*plane_pitch_and_yaw(t_plane pl)
{
	static t_flt	angles[2];
	t_vec4			h;

	ft_bzero(angles, sizeof(t_flt) * 2);
	h = pl.orientation;
	angles[0] = atan2(vec_len(point(h.x, 0, h.z)), h.y);
	h = unit_vec(vector(pl.orientation.x, 0, pl.orientation.z));
	if (h.x < 0 && h.z >= 0)
		angles[1] = asin(-h.x);
	else if (h.x < 0 && h.z < 0)
		angles[1] = M_PI - asin(-h.x);
	else if (h.x >= 0 && h.z >= 0)
		angles[1] = -asin(h.x);
	else
		angles[1] = -M_PI + asin(h.x);
	return (angles);
}

/**
 * Initializes camera's transform and inverse using the parsed orientation
 * and position.
 */
void	init_camera_transform(t_camera *cam)
{
	t_flt		*angles;

	if (vecs_are_equal(cam->orientation, (t_vec4){0}))
		cam->orientation = (t_vec4){.z = 1};
	cam->orientation = unit_vec(cam->orientation);
	angles = cam_pitch_and_yaw(cam);
	cam->transform = x_rotation_m4x4(-angles[0]);
	cam->transform = mult_m4x4(y_rotation_m4x4(angles[1]), cam->transform);
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
	// t_flt		*angles;

	if (vecs_are_equal(pl->orientation, (t_vec4){0}))
		pl->orientation = (t_vec4){.y = 1};
	pl->orientation = unit_vec(pl->orientation);
	// angles = plane_pitch_and_yaw(*pl);
	// pl->transform = x_rotation_m4x4(angles[0]);
	// pl->transform = mult_m4x4(y_rotation_m4x4(-angles[1]), pl->transform);
	pl->transform = identity_m4x4();
	pl->transform = mult_m4x4(translation_m4x4(pl->pos), pl->transform);
	pl->inverse = inverse_m4x4(pl->transform);
}

/**
 * Initializes cylinder's transform and inverse using the parsed orientation
 * and position.
 */
void	init_cylinder_transform(t_cylinder *cyl)
{
	t_flt	*angles;
	t_plane	pl;

	if (vecs_are_equal(cyl->orientation, (t_vec4){0}))
		cyl->orientation = (t_vec4){.y = 1};
	cyl->orientation = unit_vec(cyl->orientation);
	pl.orientation = cyl->orientation;
	angles = plane_pitch_and_yaw(pl);
	cyl->transform = x_rotation_m4x4(angles[0]);
	cyl->transform = mult_m4x4(y_rotation_m4x4(-angles[1]), cyl->transform);
	cyl->transform = mult_m4x4(translation_m4x4(cyl->pos), cyl->transform);
	cyl->inverse = inverse_m4x4(cyl->transform);
}
