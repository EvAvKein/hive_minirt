/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resetting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 13:31:26 by jvarila           #+#    #+#             */
/*   Updated: 2025/08/15 14:31:28 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	reset_scene2(void);

void	reset_camera(void)
{
	t_camera *const	cam = dat()->elems.camera;

	dat()->pause_threads = true;
	cam->pos = cam->initial_pos;
	cam->orientation = cam->initial_orientation;
	cam->fov = cam->initial_fov;
	init_camera_transform(cam);
	setup_pixel_grid(dat()->img->width, dat()->img->height);
	ft_putendl_fd("Reset camera", STDOUT_FILENO);
	reset_rendering_threads();
}

void	reset_object(void)
{
	t_obj	ob;

	dat()->pause_threads = true;
	ob = match_selected_object();
	ob.pos = ob.pos0;
	ob.orie = ob.orie0;
	update_selected_object(ob);
	if (ob.type == SPHERE)
		init_sphere_transform((t_sphere *)dat()->selected_obj.obj);
	else if (ob.type == CYLINDER)
		init_cylinder_transform((t_cylinder *)dat()->selected_obj.obj);
	else if (ob.type == PLANE)
		init_plane_transform((t_plane *)dat()->selected_obj.obj);
	else if (ob.type == CONE)
		init_cone_transform((t_cone *)dat()->selected_obj.obj);
	printf("Reset %s\n", obj_type_to_str(ob.type));
	reset_rendering_threads();
}

void	reset_scene(void)
{
	void		*o;
	t_ray_x_obj	selected;

	dat()->pause_threads = true;
	selected = dat()->selected_obj;
	o = dat()->elems.spheres;
	dat()->selected_obj.obj_type = SPHERE;
	while (o)
	{
		dat()->selected_obj.obj = o;
		reset_object();
		o = ((t_sphere *)o)->next;
	}
	o = dat()->elems.planes;
	dat()->selected_obj.obj_type = PLANE;
	while (o)
	{
		dat()->selected_obj.obj = o;
		reset_object();
		o = ((t_plane *)o)->next;
	}
	reset_scene2();
	dat()->selected_obj = selected;
	reset_camera();
}

static void	reset_scene2(void)
{
	void	*o;

	o = dat()->elems.cylinders;
	dat()->selected_obj.obj_type = CYLINDER;
	while (o)
	{
		dat()->selected_obj.obj = o;
		reset_object();
		o = ((t_cylinder *)o)->next;
	}
	o = dat()->elems.cones;
	dat()->selected_obj.obj_type = CONE;
	while (o)
	{
		dat()->selected_obj.obj = o;
		reset_object();
		o = ((t_cone *)o)->next;
	}
}
