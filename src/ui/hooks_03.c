/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_03.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 10:11:06 by ekeinan           #+#    #+#             */
/*   Updated: 2025/08/15 10:02:29 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Sets mouse x and y positions in the data struct.
 */
void	mouse_pos_hook(double x, double y, void *param)
{
	(void) param;
	dat()->mouse.x = x;
	dat()->mouse.y = y;
}

/**
 * Sets selected object in the data struct.
 */
void	select_obj_hook(mouse_key_t key, action_t action,
			modifier_key_t modifier, void *param)
{
	t_ray	ray;
	t_obj	ob;

	(void) action;
	(void) modifier;
	(void) param;
	if (key != MLX_MOUSE_BUTTON_LEFT || action != MLX_RELEASE)
		return ;
	ray = ray_for_pixel(dat()->mouse.y * dat()->img->width + dat()->mouse.x);
	cast_ray_at_objs(&ray, &dat()->elems, NULL);
	if (ray.closest_hit.obj)
	{
		dat()->selected_obj = ray.closest_hit;
		ob = match_selected_object();
		printf("Object type:		" CLR_BOLD "%s" CLR_RESET "\n",
			obj_type_to_str(ray.closest_hit.obj_type));
		ft_putstr_fd("Object position:	", STDOUT_FILENO);
		print_vec(ob.pos);
		ft_putstr_fd("Object orientation:	", STDOUT_FILENO);
		print_vec(ob.orie);
	}
}
