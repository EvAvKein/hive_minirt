/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:43:16 by ekeinan           #+#    #+#             */
/*   Updated: 2025/06/25 16:25:36 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * 
 * @param str		The string being parsed.
 * 
 * @param parse_i	The parsing index.
 * 
 * @param dest		The destination for the parsed `long long` value.
 *
 * @returns Whether parsing was successful.
 * 
 */
static bool	longlong_parse(char *str, size_t *parse_i, long long *dest)
{
	const bool		negative = (str[*parse_i] == '-') && ++(*parse_i);
	long long		num;
	const size_t	initial_i = (*parse_i - negative);

	num = 0;
	if (!ft_strncmp("-9223372036854775807", &str[*parse_i - negative], 21))
	{
		*dest = -9223372036854775807;
		return (true);
	}
	while (ft_isdigit(str[*parse_i]))
	{
		if ((num > (LLONG_MAX / 10))
			|| ((num * 10) > (LLONG_MAX - str[*parse_i] - '0')))
			return (false);
		num *= 10;
		num += str[(*parse_i)++] - '0';
	}
	if (negative)
		num = -num;
	if ((*parse_i - negative - initial_i) == 0
		|| (negative && !num))
		return (false);
	*dest = num;
	return (true);
}

/**
 * 
 * @param str		The string being parsed.
 * 
 * @param parse_i	The parsing index.
 * 
 * @param dest		The destination for the parsed `float` value.
 * 
 * @returns Whether parsing was successful.
 * 
 */
bool	flt_parse(char *str, size_t *parse_i, t_flt *dest)
{
	long long	integer;
	long long	decimal;
	size_t	decimal_len;

	if (!longlong_parse(str, parse_i, &integer))
		return (false);
	if (!str[*parse_i] || is_space(str[*parse_i]) || str[*parse_i] == ',')
	{
		*dest = integer;
		skip_spaces(str, parse_i);
		return (true);
	}
	if (str[(*parse_i)++] != '.')
		return (false);
	decimal_len = *parse_i;
	if (!longlong_parse(str, parse_i, &decimal))
		return (false);
	if (decimal < 0)
		return (false);
	decimal_len = *parse_i - decimal_len;
	*dest = (t_flt)integer + ((t_flt)decimal / pow(10, decimal_len));
	skip_spaces(str, parse_i);
	return (true);
}

/**
 * 
 * @param str		The string being parsed.
 * 
 * @param parse_i	The parsing index.
 * 
 * @param dest		The destination for the parsed `uint8` value.
 * 
 * @returns Whether parsing was successful.
 * 
 */
bool	uint8_parse(char *str, size_t *parse_i, uint8_t *dest)
{
	long long	value;

	if (!longlong_parse(str, parse_i, &value))
		return (false);
	if (value < 0 || value > UINT8_MAX)
		return (false);
	*dest = value;
	skip_spaces(str, parse_i);
	return (true);
}
