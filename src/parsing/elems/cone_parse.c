/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 10:25:20 by ekeinan           #+#    #+#             */
/*   Updated: 2025/08/04 18:56:14 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline bool	cone_parse_pt2(
						t_cone *cone, char *str, size_t *parse_i);
static inline bool	cone_parse_pt3(
						t_cone *cone, char *str, size_t *parse_i);

/**
 *
 * Parses the line's cone data,
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
bool	cone_parse(char *str, size_t *parse_i)
{
	t_cone	cone;
	t_cone	**ptr_to_next;

	cone = (t_cone){};
	skip_letters_and_trailing_spaces(str, parse_i);
	if (!vec4_parse(str, parse_i, &cone.pos, true)
		|| !is_space(str[*parse_i - 1]))
		return (print_err("Invalid cone position"));
	if (!cone_parse_pt2(&cone, str, parse_i)
		|| !cone_parse_pt3(&cone, str, parse_i))
		return (false);
	ptr_to_next = &dat()->elems.cones;
	while (*ptr_to_next)
		ptr_to_next = &(*ptr_to_next)->next;
	*ptr_to_next = malloc(sizeof(t_cone));
	if (!*ptr_to_next)
	{
		if (cone.texture)
			mlx_delete_texture(cone.texture);
		return (print_err("Failed to allocate memory for cone"));
	}
	**ptr_to_next = cone;
	return (true);
}

static inline bool	cone_parse_pt2(t_cone *cone,
						char *str, size_t *parse_i)
{
	uint8_t	num;

	if (!vec4_parse(str, parse_i, &cone->orientation, false)
		|| !is_normalized_vec(cone->orientation)
		|| !is_space(str[*parse_i - 1]))
		return (print_err("Invalid cone orientation"));
	if (!flt_parse(str, parse_i, &cone->diam)
		|| cone->diam < EPSILON || !is_space(str[*parse_i - 1]))
		return (print_err("Invalid cone diameter"));
	if (!flt_parse(str, parse_i, &cone->height)
		|| cone->height < EPSILON || !is_space(str[*parse_i - 1]))
		return (print_err("Invalid cone height"));
	if (!uint8_parse(str, parse_i, &num)
		|| num < 1 || num > 2
		|| !is_space(str[*parse_i - 1]))
		return (false);
	cone->single = num % 2;
	return (true);
}

static inline bool	cone_parse_pt3(t_cone *cone,
						char *str, size_t *parse_i)
{
	if (!rgb_parse(str, parse_i, &cone->color)
		|| !is_space(str[*parse_i - 1]))
		return (print_err("Invalid cone color"));
	if (!optional_pattern_name_parse(str, parse_i, &cone->pattern)
		&& !optional_asset_parse(str, parse_i, &cone->texture))
		return (print_err("Invalid cone pattern name or texture"));
	if (!cone->texture && !optional_pattern_color_parse(str, parse_i,
			cone->pattern, &cone->pattern_color))
		return (print_err("Invalid cone pattern color"));
	if (!is_end(str[*parse_i]))
	{
		if (!cone->texture)
			return (print_err("Invalid cone data after pattern color"));
		mlx_delete_texture(cone->texture);
		return (print_err("Invalid cone data after texture"));
	}
	return (true);
}
