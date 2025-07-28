/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pattern.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 14:58:41 by ekeinan           #+#    #+#             */
/*   Updated: 2025/07/28 10:11:34 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	pattern_name_match_and_skip_i(
						char *str, size_t *parse_i, char *pattern_name)
{
	const size_t	name_len = ft_strlen(pattern_name);

	if (ft_strncmp(&str[*parse_i], pattern_name, name_len))
		return (false);
	*parse_i += name_len;
	return (is_space(str[*parse_i]) || !str[*parse_i]);
}

/**
 *
 * @param str			The string being parsed.
 *
 * @param parse_i		The parsing index.
 *
 * @param dest			The destination for the parsed pattern type.
 *
 * @returns Whether parsing was successful.
 *
 */
bool	optional_pattern_name_parse(char *str, size_t *parse_i, t_pattern *dest)
{
	if (!str[*parse_i])
		*dest = SOLID;
	else if (pattern_name_match_and_skip_i(str, parse_i, "checkerboard"))
		*dest = CHECKERBOARD;
	else if (pattern_name_match_and_skip_i(str, parse_i, "candy"))
		*dest = CANDY;
	else if (pattern_name_match_and_skip_i(str, parse_i, "circus"))
		*dest = CIRCUS;
	else if (pattern_name_match_and_skip_i(str, parse_i, "lines"))
		*dest = LINES;
	else if (pattern_name_match_and_skip_i(str, parse_i, "angel"))
		*dest = ANGEL;
	else if (pattern_name_match_and_skip_i(str, parse_i, "beams"))
		*dest = BEAMS;
	else
		return (false);
	if (str[*parse_i] && !is_space(str[*parse_i]))
		return (false);
	skip_spaces(str, parse_i);
	return (true);
}

/**
 *
 * @param str			The string being parsed.
 *
 * @param parse_i		The parsing index.
 *
 * @param pattern_name	The type of the pattern whose color is being parsed,
 * 						to set `dest` to the pattern's default color
 * 						if no color was parsed.
 *
 * @param dest			The destination for the parsed pattern color.
 *
 * @returns Whether parsing was successful.
 *
 */
bool	optional_pattern_color_parse(char *str, size_t *parse_i,
			t_pattern pattern_name, t_8bit_color *dest)
{
	if (!str[*parse_i])
	{
		*dest = vec4_to_color(mat_of_pattern(pattern_name).color).bit;
		return (true);
	}
	else if (!rgb_parse(str, parse_i, dest))
		return (false);
	skip_spaces(str, parse_i);
	return (true);
}
