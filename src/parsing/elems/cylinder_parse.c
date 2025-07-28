/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 10:25:20 by ekeinan           #+#    #+#             */
/*   Updated: 2025/07/28 10:10:03 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline bool	cylinder_parse_latter_half(
						t_cylinder *cylinder, char *str, size_t *parse_i);

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
		|| !is_space(str[*parse_i - 1]))
		return (print_err("invalid cylinder diameter"));
	if (!cylinder_parse_latter_half(&cylinder, str, parse_i))
		return (false);
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

static inline bool	cylinder_parse_latter_half(t_cylinder *cylinder,
						char *str, size_t *parse_i)
{
	if (!flt_parse(str, parse_i, &cylinder->height)
		|| !is_space(str[*parse_i - 1]))
		return (print_err("invalid cylinder height"));
	if (!rgb_parse(str, parse_i, &cylinder->color.bit)
		|| !is_space(str[*parse_i - 1]))
		return (print_err("invalid cylinder color"));
	if (!optional_pattern_name_parse(str, parse_i, &cylinder->pattern))
		return (print_err("invalid cylinder pattern name"));
	if (!optional_pattern_color_parse(str, parse_i,
			cylinder->pattern, &cylinder->pattern_color))
		return (print_err("invalid cylinder pattern color"));
	if (str[*parse_i])
		return (print_err("invalid cylinder data after pattern color"));
	return (true);
}
