/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_checks_and_skips.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:52:34 by ekeinan           #+#    #+#             */
/*   Updated: 2025/08/08 17:43:22 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @returns Whether the provided `c` is a line-endiing character
 * (a null terminator, or the comment indicator '#').
 */
inline bool	is_end(char c)
{
	return (c == '\0' || c == '#');
}

/**
 * @returns Whether the provided `c` is a space character
 * (an actual space, or horizontal/vertical tab, or newline,
 * or form feed, or carriage return).
 */
inline bool	is_space(char c)
{
	return (c == ' ' || (c <= '\r' && c >= '\t'));
}

/**
 * Progresses the parsing index until the string's next non-space character.
 */
void	skip_spaces(char *str, size_t *parse_i)
{
	while (is_space(str[*parse_i]))
		(*parse_i)++;
}

/**
 * Progresses the parsing index past letter characters
 * and then past all following space characters.
 */
void	skip_letters_and_trailing_spaces(char *str, size_t *parse_i)
{
	while (ft_isalpha(str[*parse_i]))
		(*parse_i)++;
	skip_spaces(str, parse_i);
}

