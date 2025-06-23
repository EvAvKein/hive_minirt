/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:52:34 by ekeinan           #+#    #+#             */
/*   Updated: 2025/06/18 13:55:00by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * 
 * @returns Whether the provided `c` is a space character
 * (an actual space, or horizontal/vertical tab, or newline,
 * or form feed, or carriage return).
 * 
 */
inline bool	is_space(char c)
{
	return (c == ' ' || (c <= '\r' && c >= '\t'));
}

/**
 * 
 * Progresses the parsing index until the string's next non-space character.
 * 
 */
void	skip_spaces(char *str, size_t *parse_i)
{
	while (is_space(str[*parse_i]))
		(*parse_i)++;
}

/**
 * 
 * TODO: Write these docs
 * 
 */
bool	in_flt_range(t_flt checked, t_flt min, t_flt max)
{
	return (checked >= min && checked <= max);
}

/**
 * 
 * TODO: Write these docs
 * 
 */
bool	is_flt_normalized_vec(t_vec4 vec)
{
	return (in_flt_range(vec.axis.x, -1.f, 1.f)
			&& in_flt_range(vec.axis.y, -1.f, 1.f)
			&& in_flt_range(vec.axis.z, -1.f, 1.f));
}
