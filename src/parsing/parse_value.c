/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:43:16 by ekeinan           #+#    #+#             */
/*   Updated: 2025/06/23 20:34:42 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * 
 * TODO: Write these docs
 * 
 */
static bool	ulonglong_parse(
	char *str, size_t *parse_i, unsigned long long *dest)
{
	size_t				i;
	unsigned long long	num;
	bool				negative;

	i = *parse_i;
	num = 0;
	negative = (str[i] == '-');
	if (negative)
		i++;
	while (ft_isdigit(str[i]))
	{
		if (num > ULLONG_MAX / 10
			|| num * 10 > ULLONG_MAX - (str[i++] - '0'))
			return (false);
		num *= 10;
		num += str[i++] - '0';
	}
	if ((i - negative - *parse_i) == 0)
		return (false);
	*parse_i += (i - *parse_i);
	*dest = num;
	return (true);
}

/**
 * 
 * TODO: Write these docs
 * 
 */
bool	flt_parse(char *str, size_t *parse_i, t_flt *dest)
{
	unsigned long long	integer;
	unsigned long long	decimal;
	size_t	decimal_len;

	if (!ulonglong_parse(str, parse_i, &integer))
		return (false);
	if (!str[*parse_i] || is_space(str[*parse_i]) || str[*parse_i] == ',')
	{
		*dest = integer;
		return (true);
	}
	if (str[(*parse_i)++] != '.')
		return (false);
	decimal_len = *parse_i;
	if (!ulonglong_parse(str, parse_i, &decimal))
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
 * TODO: Write these docs
 * 
 */
bool	uint8_parse(char *str, size_t *parse_i, uint8_t *dest)
{
	unsigned long long	value;

	if (!ulonglong_parse(str, parse_i, &value)
		|| value < 0 || value > UINT8_MAX)
		return (false);
	*dest = value;
	skip_spaces(str, parse_i);
	return (true);
}
