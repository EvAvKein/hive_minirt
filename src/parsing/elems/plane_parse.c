/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 18:21:58 by ekeinan           #+#    #+#             */
/*   Updated: 2025/08/07 20:38:56 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline bool	plane_parse_pt2(
						t_plane *plane, char *str, size_t *parse_i);

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

	plane = (t_plane){};
	skip_letters_and_trailing_spaces(str, parse_i);
	if (!vec4_parse(str, parse_i, &plane.pos, true)
		|| !is_space(str[*parse_i - 1]))
		return (print_err("invalid plane position"));
	if (!plane_parse_pt2(&plane, str, parse_i))
		return (false);
	ptr_to_next = &g_data.elems.planes;
	while (*ptr_to_next)
		ptr_to_next = &(*ptr_to_next)->next;
	*ptr_to_next = malloc(sizeof(t_plane));
	if (!*ptr_to_next)
	{
		if (plane.texture)
			mlx_delete_texture(plane.texture);
		return (print_err("failed to allocate memory for plane"));
	}
	**ptr_to_next = plane;
	return (true);
}

static inline bool	plane_parse_pt2(
			t_plane *plane, char *str, size_t *parse_i)
{
	if (!vec4_parse(str, parse_i, &plane->orientation, false)
		|| !is_normalized_vec(plane->orientation)
		|| !is_space(str[*parse_i - 1]))
		return (print_err("invalid plane orientation"));
	if (!rgb_parse(str, parse_i, &plane->color)
		|| !is_space(str[*parse_i - 1]))
		return (print_err("invalid plane color"));
	if (!optional_pattern_name_parse(str, parse_i, &plane->pattern)
		&& !optional_asset_parse(str, parse_i, &plane->texture))
		return (print_err("invalid plane pattern name or texture"));
	if (!plane->texture && !optional_pattern_color_parse(str, parse_i,
			plane->pattern, &plane->pattern_color))
		return (print_err("invalid plane pattern color"));
	if (str[*parse_i])
	{
		if (!plane->texture)
			return (print_err("invalid plane data after pattern color"));
		mlx_delete_texture(plane->texture);
		return (print_err("invalid plane data after texture"));
	}
	return (true);
}
