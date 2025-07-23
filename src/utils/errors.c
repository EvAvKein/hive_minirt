/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 09:26:46 by ekeinan           #+#    #+#             */
/*   Updated: 2025/07/22 09:59:38 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 *
 * Prints to STDERR "Error" and a newline,
 * followed by "miniRT: ", the provided string, and a newline.
 *
 * @param error	String containing error message to print
 *
 * @returns `false`
 *
 */
bool	print_err(char *error)
{
	ft_dprintf(STDERR_FILENO, "Error\nminiRT: %s\n", error);
	return (false);
}
