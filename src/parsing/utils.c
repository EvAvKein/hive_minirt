/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:52:34 by ekeinan           #+#    #+#             */
/*   Updated: 2025/06/26 11:24:25 by jvarila          ###   ########.fr       */
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
 * Progresses the parsing index past letter characters
 * and then past all following space characters.
 * 
 */
void	skip_letters_and_trailing_spaces(char *str, size_t *parse_i)
{
	while (ft_isalpha(str[*parse_i]))
		(*parse_i)++;
	skip_spaces(str, parse_i);
}

/**
 * 
 * @returns Whether the provided `checked`
 * is within the provided minimum and maximum (inclusive).
 * 
 */
inline bool	in_flt_range(t_flt checked, t_flt min, t_flt max)
{
	return (checked >= min && checked <= max);
}

/**
 * 
 * @returns Whether the provided vector's
 * x, y, and z axes are all between -1 and 1 (inclusive).
 * 
 */
inline bool	is_normalized_vec(t_vec4 vec)
{
	return (in_flt_range(vec.axis.x, -1.f, 1.f)
		&& in_flt_range(vec.axis.y, -1.f, 1.f)
		&& in_flt_range(vec.axis.z, -1.f, 1.f));
}
