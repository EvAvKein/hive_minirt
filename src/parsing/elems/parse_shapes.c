/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 10:25:20 by ekeinan           #+#    #+#             */
/*   Updated: 2025/07/16 10:37:08 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 *
 * Parses the line's sphere data,
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
bool	sphere_parse(char *str, size_t *parse_i)
{
	t_sphere	sphere;
	t_sphere	**ptr_to_next;

	skip_letters_and_trailing_spaces(str, parse_i);
	if (!vec4_parse(str, parse_i, &sphere.pos, true)
		|| !is_space(str[*parse_i - 1]))
		return (print_err("invalid sphere position"));
	if (!flt_parse(str, parse_i, &sphere.radius)
		|| !is_space(str[*parse_i - 1]))
		return (print_err("invalid sphere diameter"));
	sphere.radius /= 2;
	if (!rgb_parse(str, parse_i, &sphere.color.bit))
		return (print_err("invalid sphere color"));
	if (str[*parse_i])
		return (print_err("invalid sphere data after color"));
	sphere.next = NULL;
	ptr_to_next = &get_data()->elems.spheres;
	while (*ptr_to_next)
		ptr_to_next = &(*ptr_to_next)->next;
	*ptr_to_next = malloc(sizeof(t_sphere));
	if (!*ptr_to_next)
		return (print_err("failed to allocate memory for sphere"));
	**ptr_to_next = sphere;
	return (true);
}

/**
 *
 * Parses the line's plane data,
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
bool	plane_parse(char *str, size_t *parse_i)
{
	t_plane	plane;
	t_plane	**ptr_to_next;

	skip_letters_and_trailing_spaces(str, parse_i);
	if (!vec4_parse(str, parse_i, &plane.pos, true)
		|| !is_space(str[*parse_i - 1]))
		return (print_err("invalid plane position"));
	if (!vec4_parse(str, parse_i, &plane.orientation, false)
		|| !is_normalized_vec(plane.orientation)
		|| !is_space(str[*parse_i - 1]))
		return (print_err("invalid plane orientation"));
	if (!rgb_parse(str, parse_i, &plane.color.bit))
		return (print_err("invalid plane color"));
	if (str[*parse_i])
		return (print_err("invalid plane data after color"));
	plane.next = NULL;
	ptr_to_next = &get_data()->elems.planes;
	while (*ptr_to_next)
		ptr_to_next = &(*ptr_to_next)->next;
	*ptr_to_next = malloc(sizeof(t_plane));
	if (!*ptr_to_next)
		return (print_err("failed to allocate memory for plane"));
	**ptr_to_next = plane;
	return (true);
}

/**
 *
 * Parses the line's cylinder data,
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
bool	cylinder_parse(char *str, size_t *parse_i)
{
	t_cylinder	cylinder;
	t_cylinder	**ptr_to_next;

	skip_letters_and_trailing_spaces(str, parse_i);
	if (!vec4_parse(str, parse_i, &cylinder.pos, true)
		|| !is_space(str[*parse_i - 1]))
		return (print_err("invalid cylinder position"));
	if (!vec4_parse(str, parse_i, &cylinder.orientation, false)
		|| !is_normalized_vec(cylinder.orientation)
		|| !is_space(str[*parse_i - 1]))
		return (print_err("invalid cylinder orientation"));
	if (!flt_parse(str, parse_i, &cylinder.diam)
		|| !flt_parse(str, parse_i, &cylinder.height))
		return (print_err("invalid cylinder diameter/height"));
	if (!rgb_parse(str, parse_i, &cylinder.color.bit) || str[*parse_i])
		return (print_err("invalid cylinder color (or data after color)"));
	cylinder.next = NULL;
	ptr_to_next = &get_data()->elems.cylinders;
	while (*ptr_to_next)
		ptr_to_next = &(*ptr_to_next)->next;
	*ptr_to_next = malloc(sizeof(t_cylinder));
	if (!*ptr_to_next)
		return (print_err("failed to allocate memory for cylinder"));
	**ptr_to_next = cylinder;
	return (true);
}
