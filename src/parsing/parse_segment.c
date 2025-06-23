/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_segment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:33:37 by ekeinan           #+#    #+#             */
/*   Updated: 2025/06/23 11:38:33 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * 
 * TODO: Write these docs
 * 
 */
bool	rgba_parse(char *str, size_t *parse_i, t_8bit_color *dest)
{
	if (!uint8_parse(str, parse_i, &dest->channel.r)
		|| is_space(str[(*parse_i) - 1])
		|| str[(*parse_i)++] != ',')
		return (false);
	if (!uint8_parse(str, parse_i, &dest->channel.g)
		|| is_space(str[(*parse_i) - 1])
		|| str[(*parse_i)++] != ',')
		return (false);
	if (!uint8_parse(str, parse_i, &dest->channel.b))
		return (false);
	dest->channel.a = UINT8_MAX;
	return (true);
}

/**
 * 
 * TODO: Write these docs
 * 
 */
bool	vec4_parse(char *str, size_t *parse_i, t_vec4 *dest, bool is_point)
{
	if (!flt_parse(str, parse_i, &dest->axis.x)
		|| is_space(str[(*parse_i) - 1])
		|| str[(*parse_i)++] != ',')
		return (false);
	if (!flt_parse(str, parse_i, &dest->axis.y)
		|| is_space(str[(*parse_i) - 1])
		|| str[(*parse_i)++] != ',')
		return (false);
	if (!flt_parse(str, parse_i, &dest->axis.z))
		return (false);
	if (is_point)
		dest->axis.w = 1;
	else
		dest->axis.w = 0;
	return (true);
}


