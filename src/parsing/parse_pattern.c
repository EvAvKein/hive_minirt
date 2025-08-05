/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pattern.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 14:58:41 by ekeinan           #+#    #+#             */
/*   Updated: 2025/08/08 17:07:57 by ekeinan          ###   ########.fr       */
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
	return (is_space(str[*parse_i]) || is_end(str[*parse_i]));
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
	if (is_end(str[*parse_i])
		|| pattern_name_match_and_skip_i(str, parse_i, "solid"))
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
	if (!is_end(str[*parse_i]) && !is_space(str[*parse_i]))
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
			t_pattern pattern_name, t_flt_color *dest)
{
	if (is_end(str[*parse_i]))
	{
		*dest = mat_of_pattern(pattern_name).color;
		return (true);
	}
	else if (!rgb_parse(str, parse_i, dest))
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
 * @param dest			The destination for the asset image.
 *
 * @returns Whether parsing was successful.
 *
 */
bool	optional_asset_parse(char *str, size_t *parse_i, mlx_texture_t **dest)
{
	size_t			path_i;
	bool			manually_terminated_str;

	*dest = NULL;
	if (!str[*parse_i])
		return (true);
	path_i = 0;
	while (str[*parse_i + path_i] && !is_space(str[*parse_i + path_i]))
		path_i++;
	manually_terminated_str = is_space(str[*parse_i + path_i]);
	if (manually_terminated_str)
		str[*parse_i + path_i] = '\0';
	*dest = mlx_load_png(&str[*parse_i]);
	if (*dest)
		*parse_i += path_i + manually_terminated_str;
	return (!!*dest);
}
