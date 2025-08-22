/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 10:25:20 by ekeinan           #+#    #+#             */
/*   Updated: 2025/08/08 16:46:58 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline bool	triangle_parse_latter_half(
						t_triangle *triangle, char *str, size_t *parse_i);
static inline bool	invalid_pattern(char *str, size_t *parse_i);
static inline bool	pattern_name_match(char *str, size_t *parse_i,
						char *pattern_name);

/**
 *
 * Parses the line's triangle data,
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
bool	triangle_parse(char *str, size_t *parse_i)
{
	t_triangle	triangle;
	t_triangle	**ptr_to_next;

	skip_letters_and_trailing_spaces(str, parse_i);
	if (!vec4_parse(str, parse_i, &triangle.pos1, true)
		|| !is_space(str[*parse_i - 1]))
		return (print_err("Invalid triangle position 1"));
	if (!vec4_parse(str, parse_i, &triangle.pos2, true)
		|| !is_space(str[*parse_i - 1]))
		return (print_err("Invalid triangle position 2"));
	if (!vec4_parse(str, parse_i, &triangle.pos3, true)
		|| !is_space(str[*parse_i - 1]))
		return (print_err("Invalid triangle position 3"));
	if (!triangle_parse_latter_half(&triangle, str, parse_i))
		return (false);
	triangle.next = NULL;
	ptr_to_next = &dat()->elems.triangles;
	while (*ptr_to_next)
		ptr_to_next = &(*ptr_to_next)->next;
	*ptr_to_next = malloc(sizeof(t_triangle));
	if (!*ptr_to_next)
		return (print_err("Failed to allocate memory for triangle"));
	**ptr_to_next = triangle;
	return (true);
}

static inline bool	triangle_parse_latter_half(t_triangle *triangle,
						char *str, size_t *parse_i)
{
	if (!rgb_parse(str, parse_i, &triangle->color)
		|| (!is_end(str[*parse_i]) && !is_space(str[*parse_i - 1])))
		return (print_err("Invalid triangle color"));
	if (invalid_pattern(str, parse_i))
		return (print_err("incompatible pattern for triangle"));
	if (!optional_pattern_name_parse(str, parse_i, &triangle->pattern))
		return (print_err("Invalid triangle pattern name"));
	if (!optional_pattern_color_parse(str, parse_i,
			triangle->pattern, &triangle->pattern_color))
		return (print_err("Invalid triangle pattern color"));
	if (!is_end(str[*parse_i]))
		return (print_err("Invalid triangle data after pattern color"));
	return (true);
}

static inline bool	invalid_pattern(char *str, size_t *parse_i)
{
	return (pattern_name_match(str, parse_i, "checkerboard")
		|| pattern_name_match(str, parse_i, "beams")
		|| pattern_name_match(str, parse_i, "circus"));
}

static inline bool	pattern_name_match(char *str, size_t *parse_i,
						char *pattern_name)
{
	const size_t	len = ft_strlen(pattern_name);

	return (!ft_strncmp(&str[*parse_i], pattern_name, len)
		&& (!str[*parse_i + len] || is_space(str[*parse_i + len])));
}
