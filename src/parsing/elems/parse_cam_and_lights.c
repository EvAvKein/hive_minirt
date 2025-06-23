/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cam_and_lights.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:32:44 by ekeinan           #+#    #+#             */
/*   Updated: 2025/06/23 20:29:08 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	ambient_light_parse(char *str, size_t *parse_i)
{
	t_ambient_light	ambient_light;
	t_ambient_light	*node;
	
	if (get_data()->elems.ambient_light)
		return (false);
	skip_spaces(str, parse_i);
	if (!flt_parse(str, parse_i, &ambient_light.brightness)
		|| !in_flt_range(ambient_light.brightness, 0.f, 1.f)
		|| !is_space(str[*parse_i]))
		return (false);
	skip_spaces(str, parse_i);
	if (!rgba_parse(str, parse_i, &ambient_light.color.bit))
		return (false);
	skip_spaces(str, parse_i);
	if (str[*parse_i])
		return (false);
	node = malloc(sizeof(t_ambient_light));
	if (!node)
		return (false);
	*node = ambient_light;
	get_data()->elems.ambient_light = node;
	return (true);
}

bool	camera_parse(char *str, size_t *parse_i)
{
	t_camera	camera;
	t_camera	*node;
	
	if (get_data()->elems.camera)
		return (false);
	skip_spaces(str, parse_i);
	if (!vec4_parse(str, parse_i, &camera.pos, true)
		|| !is_space(str[*parse_i - 1]))
		return (false);
	if (!vec4_parse(str, parse_i, &camera.orientation, false)
		|| !is_flt_normalized_vec(camera.orientation)
		|| !is_space(str[*parse_i - 1]))
		return (false);
	if (!uint8_parse(str, parse_i, &camera.fov)
		|| camera.fov < 0 || camera.fov > 180)
		return (false);
	if (str[*parse_i])
		return (false);
	node = malloc(sizeof(t_camera));
	if (!node)
		return (false);
	*node = camera;
	get_data()->elems.camera = node;
	return (true);
}

bool	light_parse(char *str, size_t *parse_i)
{
	t_light	light;
	t_light	**ptr_to_next;
	
	skip_spaces(str, parse_i);
	if (!vec4_parse(str, parse_i, &light.pos, true)
		|| !is_space(str[*parse_i - 1]))
		return (false);
	if (!flt_parse(str, parse_i, &light.brightness)
		|| !in_flt_range(light.brightness, 0.f, 1.f))
		return (false);
	// if (!is_space(str[*parse_i - 1])
	//		|| !rgba_parse(str, parse_i, &light.color.bit)) // bonus 
	// 	return (false);
	if (str[*parse_i])
		return (false);
	ptr_to_next = &get_data()->elems.lights;
	while (*ptr_to_next && (*ptr_to_next)->next)
		ptr_to_next = &(*ptr_to_next)->next;
	*ptr_to_next = malloc(sizeof(t_light));
	if (!*ptr_to_next)
		return (false);
	**ptr_to_next = light;
	return (true);
}
