/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 09:26:46 by ekeinan           #+#    #+#             */
/*   Updated: 2025/06/26 16:00:22 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 *
 * Prints to STDERR "Error" and a newline,
 * followed by "miniRT: ", the provided string, and a newline.
 *
 * @returns `false`
 *
 */
bool	print_err(char *error)
{
	ft_dprintf(STDERR_FILENO, "Error\nminiRT: %s\n", error);
	return (false);
}
