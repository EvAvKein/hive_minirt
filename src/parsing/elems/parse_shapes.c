/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 10:25:20 by ekeinan           #+#    #+#             */
/*   Updated: 2025/06/23 10:47:18by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	sphere_parse(char *str, size_t *parse_i)
{
	t_sphere	sphere;
	t_sphere	**ptr_to_next;
	
	skip_spaces(str, parse_i);
	if (!vec4_parse(str, parse_i, &sphere.pos, true)
		|| !is_space(str[*parse_i - 1]))
		return (false);
	if (!flt_parse(str, parse_i, &sphere.radius)
		|| !is_space(str[*parse_i - 1]))
		return (false);
	sphere.radius /= 2;
	if (!rgba_parse(str, parse_i, &sphere.color.bit))
		return (false);
	if (str[*parse_i])
		return (false);
	ptr_to_next = &get_data()->elems.spheres;
	while (*ptr_to_next && (*ptr_to_next)->next)
		ptr_to_next = &(*ptr_to_next)->next;
	*ptr_to_next = malloc(sizeof(t_sphere));
	if (!*ptr_to_next)
		return (false);
	**ptr_to_next = sphere;
	return (true);
}

bool	plane_parse(char *str, size_t *parse_i)
{
	t_plane	plane;
	t_plane	**ptr_to_next;
	
	skip_spaces(str, parse_i);
	if (!vec4_parse(str, parse_i, &plane.pos, true)
		|| !is_space(str[*parse_i - 1]))
		return (false);
	if (!vec4_parse(str, parse_i, &plane.orientation, false)
		|| !is_flt_normalized_vec(plane.orientation)
		|| !is_space(str[*parse_i - 1]))
		return (false);
	if (!rgba_parse(str, parse_i, &plane.color.bit))
		return (false);
	if (str[*parse_i])
		return (false);
	ptr_to_next = &get_data()->elems.planes;
	while (*ptr_to_next && (*ptr_to_next)->next)
		ptr_to_next = &(*ptr_to_next)->next;
	*ptr_to_next = malloc(sizeof(t_plane));
	if (!*ptr_to_next)
		return (false);
	**ptr_to_next = plane;
	return (true);
}

bool	cylinder_parse(char *str, size_t *parse_i)
{
	t_cylinder	cylinder;
	t_cylinder	**ptr_to_next;
	
	skip_spaces(str, parse_i);
	if (!vec4_parse(str, parse_i, &cylinder.pos, true)
		|| !is_space(str[*parse_i - 1]))
		return (false);
	if (!vec4_parse(str, parse_i, &cylinder.orientation, false)
		|| !is_flt_normalized_vec(cylinder.orientation)
		|| !is_space(str[*parse_i - 1]))
		return (false);
	if (!flt_parse(str, parse_i, &cylinder.diam))
		return (false);
	if (!flt_parse(str, parse_i, &cylinder.height))
		return (false);
	if (!rgba_parse(str, parse_i, &cylinder.color.bit) || str[*parse_i])
		return (false);
	ptr_to_next = &get_data()->elems.cylinders;
	while (*ptr_to_next && (*ptr_to_next)->next)
		ptr_to_next = &(*ptr_to_next)->next;
	*ptr_to_next = malloc(sizeof(t_cylinder));
	if (!*ptr_to_next)
		return (false);
	**ptr_to_next = cylinder;
	return (true);
}
