/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cam_and_lights.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:32:44 by ekeinan           #+#    #+#             */
/*   Updated: 2025/06/26 11:26:58 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 *
 * Parses the line's ambient light data,
 * adding to to program's data structure if successful
 * (or printing an error on failure).
 *  
 * @param str		The string being parsed.
 * 
 * @param parse_i	The parsing index.
 * 
 * @returns Whether parsing was successful.
 * 
 */
bool	ambient_light_parse(char *str, size_t *parse_i)
{
	t_ambient_light	ambient_light;
	t_ambient_light	*node;

	skip_letters_and_trailing_spaces(str, parse_i);
	if (!flt_parse(str, parse_i, &ambient_light.brightness)
		|| !in_flt_range(ambient_light.brightness, 0.f, 1.f)
		|| !is_space(str[*parse_i - 1]))
		return (print_err("invalid ambient light brightness"));
	skip_spaces(str, parse_i);
	if (!rgb_parse(str, parse_i, &ambient_light.color.bit))
		return (print_err("invalid ambient light color"));
	skip_spaces(str, parse_i);
	if (str[*parse_i])
		return (print_err("invalid ambient light data after color"));
	node = malloc(sizeof(t_ambient_light));
	if (!node)
		return (print_err("failed to allocate memory for ambient light"));
	*node = ambient_light;
	get_data()->elems.ambient_light = node;
	return (true);
}

/**
 *
 * Parses the line's camera data,
 * adding to to program's data structure if successful
 * (or printing an error on failure).
 *  
 * @param str		The string being parsed.
 * 
 * @param parse_i	The parsing index.
 * 
 * @returns Whether parsing was successful.
 * 
 */
bool	camera_parse(char *str, size_t *parse_i)
{
	t_camera	camera;
	t_camera	*node;

	skip_letters_and_trailing_spaces(str, parse_i);
	if (!vec4_parse(str, parse_i, &camera.pos, true)
		|| !is_space(str[*parse_i - 1]))
		return (print_err("invalid camera position"));
	if (!vec4_parse(str, parse_i, &camera.orientation, false)
		|| !is_normalized_vec(camera.orientation)
		|| !is_space(str[*parse_i - 1]))
		return (print_err("invalid camera orientation"));
	if (!uint8_parse(str, parse_i, &camera.fov)
		|| camera.fov > 180)
		return (print_err("invalid camera field of view"));
	if (str[*parse_i])
		return (print_err("invalid camera data after field of view"));
	node = malloc(sizeof(t_camera));
	if (!node)
		return (print_err("failed to allocate memory for camera"));
	*node = camera;
	get_data()->elems.camera = node;
	return (true);
}

/**
 *
 * Parses the line's light data,
 * adding to to program's data structure if successful
 * (or printing an error on failure).
 *  
 * @param str		The string being parsed.
 * 
 * @param parse_i	The parsing index.
 * 
 * @returns Whether parsing was successful.
 * 
 */
bool	light_parse(char *str, size_t *parse_i)
{
	t_light	light;
	t_light	**ptr_to_next;

	skip_letters_and_trailing_spaces(str, parse_i);
	if (!vec4_parse(str, parse_i, &light.pos, true)
		|| !is_space(str[*parse_i - 1]))
		return (print_err("invalid light position"));
	if (!flt_parse(str, parse_i, &light.brightness)
		|| !in_flt_range(light.brightness, 0.f, 1.f))
		return (print_err("invalid light brightness"));
	if (!is_space(str[*parse_i - 1])
		|| !rgb_parse(str, parse_i, &light.color.bit))
		return (print_err("invalid light color"));
	if (str[*parse_i])
		return (print_err("invalid light data after color"));
	light.next = NULL;
	ptr_to_next = &get_data()->elems.lights;
	while (*ptr_to_next)
		ptr_to_next = &(*ptr_to_next)->next;
	*ptr_to_next = malloc(sizeof(t_light));
	if (!*ptr_to_next)
		return (print_err("failed to allocate memory for light"));
	**ptr_to_next = light;
	return (true);
}
