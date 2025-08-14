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
#include <sys/types.h>

static inline bool	cone_parse_latter_half(
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

	skip_letters_and_trailing_spaces(str, parse_i);
	if (!vec4_parse(str, parse_i, &cone.pos, true)
		|| !is_space(str[*parse_i - 1]))
		return (print_err("invalid cone position"));
	if (!vec4_parse(str, parse_i, &cone.orientation, false)
		|| !is_normalized_vec(cone.orientation)
		|| !is_space(str[*parse_i - 1]))
		return (print_err("invalid cone orientation"));
	if (!flt_parse(str, parse_i, &cone.diam)
		|| !is_space(str[*parse_i - 1]))
		return (print_err("invalid cone diameter"));
	if (!cone_parse_latter_half(&cone, str, parse_i))
		return (false);
	cone.next = NULL;
	ptr_to_next = &dat()->elems.cones;
	while (*ptr_to_next)
		ptr_to_next = &(*ptr_to_next)->next;
	*ptr_to_next = malloc(sizeof(t_cone));
	if (!*ptr_to_next)
		return (print_err("failed to allocate memory for cone"));
	**ptr_to_next = cone;
	return (true);
}

static bool	cone_amount_parse(t_cone *cone, char *str, size_t *parse_i)
{
	uint8_t	num;

	if (!uint8_parse(str, parse_i, &num)
		|| num < 1 || num > 2
		|| !is_space(str[*parse_i - 1]))
		return (false);
	cone->single = num % 2;
	return (true);
}

static inline bool	cone_parse_latter_half(t_cone *cone,
						char *str, size_t *parse_i)
{
	if (!flt_parse(str, parse_i, &cone->height)
		|| !is_space(str[*parse_i - 1]))
		return (print_err("invalid cone height"));
	if (!cone_amount_parse(cone, str, parse_i))
		return (print_err("invalid cone amount"));
	if (!rgb_parse(str, parse_i, &cone->color)
		|| !is_space(str[*parse_i - 1]))
		return (print_err("invalid cone color"));
	if (!optional_pattern_name_parse(str, parse_i, &cone->pattern))
		return (print_err("invalid cone pattern name"));
	if (!optional_pattern_color_parse(str, parse_i,
			cone->pattern, &cone->pattern_color))
		return (print_err("invalid cone pattern color"));
	if (str[*parse_i])
		return (print_err("invalid cone data after pattern color"));
	return (true);
}
