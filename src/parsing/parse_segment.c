/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_segment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:33:37 by ekeinan           #+#    #+#             */
/*   Updated: 2025/06/25 16:28:12 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * 
 * @param str		The string being parsed.
 * 
 * @param parse_i	The parsing index.
 * 
 * @param dest		The destination for the parsed RGB value.
 * 
 * @returns Whether parsing was successful.
 * 
 */
bool	rgb_parse(char *str, size_t *parse_i, t_8bit_color *dest)
{
	if (!uint8_parse(str, parse_i, &dest->r)
		|| is_space(str[(*parse_i) - 1])
		|| str[(*parse_i)++] != ',')
		return (false);
	if (!uint8_parse(str, parse_i, &dest->g)
		|| is_space(str[(*parse_i) - 1])
		|| str[(*parse_i)++] != ',')
		return (false);
	if (!uint8_parse(str, parse_i, &dest->b))
		return (false);
	dest->a = UINT8_MAX;
	return (true);
}

/**
 * 
 * @param str		The string being parsed.
 * 
 * @param parse_i	The parsing index.
 * 
 * @param dest		The destination for the parsed vector (XYZ) value.
 * 
 * @returns Whether parsing was successful.
 * 
 */
bool	vec4_parse(char *str, size_t *parse_i, t_vec4 *dest, bool is_point)
{
	if (!flt_parse(str, parse_i, &dest->x)
		|| is_space(str[(*parse_i) - 1])
		|| str[(*parse_i)++] != ',')
		return (false);
	if (!flt_parse(str, parse_i, &dest->y)
		|| is_space(str[(*parse_i) - 1])
		|| str[(*parse_i)++] != ',')
		return (false);
	if (!flt_parse(str, parse_i, &dest->z))
		return (false);
	if (is_point)
		dest->w = 1;
	else
		dest->w = 0;
	return (true);
}
