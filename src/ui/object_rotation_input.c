/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_rotation_input.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 11:36:06 by jvarila           #+#    #+#             */
/*   Updated: 2025/08/13 16:14:33 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_obj	match_selected_object2(void);

void	handle_object_rotation_input(void)
{
	t_obj	ob;
	t_vec2	axes;

	axes = get_rotation_input_axes();
	if (flts_are_equal(axes.x, 0) && flts_are_equal(axes.y, 0))
		return ;
	ob = match_selected_object();
	if (ob.type == UNKNOWN)
		return ;
	dat()->pause_threads = true;
	ob.transf = mult_m4x4(translation_m4x4(opposite_vec(ob.pos)), ob.transf);
	ob.transf = mult_m4x4(x_rotation_m4x4(axes.x), ob.transf);
	ob.transf = mult_m4x4(y_rotation_m4x4(axes.y), ob.transf);
	ob.transf = mult_m4x4(translation_m4x4(ob.pos), ob.transf);
	ob.inv = inverse_m4x4(ob.transf);
	ob.orie = transformed_vec(vector(0, 1, 0), ob.transf);
	update_selected_object(ob);
		printf("Object orientation:	");
		print_vec(ob.orie);
	reset_rendering_threads();
}

t_obj	match_selected_object(void)
{
	const t_ray_x_obj	selected = dat()->selected_obj;
	t_obj				ob;

	if (selected.obj_type == SPHERE)
	{
		ob.type = SPHERE;
		ob.pos = ((t_sphere *)selected.obj)->pos;
		ob.orie = ((t_sphere *)selected.obj)->orientation;
		ob.transf = ((t_sphere *)selected.obj)->transform;
		ob.inv = ((t_sphere *)selected.obj)->inverse;
	}
	else if (selected.obj_type == PLANE)
	{
		ob.type = PLANE;
		ob.pos = ((t_plane *)selected.obj)->pos;
		ob.orie = ((t_plane *)selected.obj)->orientation;
		ob.transf = ((t_plane *)selected.obj)->transform;
		ob.inv = ((t_plane *)selected.obj)->inverse;
	}
	else
		return (match_selected_object2());
	return (ob);
}

static t_obj	match_selected_object2(void)
{
	const t_ray_x_obj	selected = dat()->selected_obj;
	t_obj				ob;

	ob = (t_obj){};
	if (selected.obj_type == CYLINDER)
	{
		ob.type = CYLINDER;
		ob.pos = ((t_cylinder *)selected.obj)->pos;
		ob.orie = ((t_cylinder *)selected.obj)->orientation;
		ob.transf = ((t_cylinder *)selected.obj)->transform;
		ob.inv = ((t_cylinder *)selected.obj)->inverse;
	}
	else if (selected.obj_type == CONE)
	{
		ob.type = CONE;
		ob.pos = ((t_cone *)selected.obj)->pos;
		ob.orie = ((t_cone *)selected.obj)->orientation;
		ob.transf = ((t_cone *)selected.obj)->transform;
		ob.inv = ((t_cone *)selected.obj)->inverse;
	}
	return (ob);
}

static void		update_selected_object2(t_obj ob);

void	update_selected_object(t_obj ob)
{
	if (ob.type == SPHERE)
	{
		((t_sphere *)dat()->selected_obj.obj)->pos = ob.pos;
		((t_sphere *)dat()->selected_obj.obj)->orientation = ob.orie;
		((t_sphere *)dat()->selected_obj.obj)->transform = ob.transf;
		((t_sphere *)dat()->selected_obj.obj)->inverse = ob.inv;
	}
	else if (ob.type == PLANE)
	{
		((t_plane *)dat()->selected_obj.obj)->pos = ob.pos;
		((t_plane *)dat()->selected_obj.obj)->orientation = ob.orie;
		((t_plane *)dat()->selected_obj.obj)->transform = ob.transf;
		((t_plane *)dat()->selected_obj.obj)->inverse = ob.inv;
	}
	else if (ob.type == CYLINDER)
	{
		((t_cylinder *)dat()->selected_obj.obj)->pos = ob.pos;
		((t_cylinder *)dat()->selected_obj.obj)->orientation = ob.orie;
		((t_cylinder *)dat()->selected_obj.obj)->transform = ob.transf;
		((t_cylinder *)dat()->selected_obj.obj)->inverse = ob.inv;
	}
	else
		update_selected_object2(ob);
}

static void	update_selected_object2(t_obj ob)
{
	if (ob.type == CONE)
	{
		((t_cone *)dat()->selected_obj.obj)->pos = ob.pos;
		((t_cone *)dat()->selected_obj.obj)->orientation = ob.orie;
		((t_cone *)dat()->selected_obj.obj)->transform = ob.transf;
		((t_cone *)dat()->selected_obj.obj)->inverse = ob.inv;
	}
}
