/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 22:37:02 by ekeinan           #+#    #+#             */
/*   Updated: 2025/08/08 16:46:23 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline bool	sphere_parse_pt2(t_sphere *sphere,
						char *str, size_t *parse_i);

/**
 *
 * Parses the line's sphere data,
 * adding to to program's data structure if successful
 * (or printing an error on failure).
 *
 * @param str		The string being parsed.
 *
 * @param parse_i	The parsing index.
 *
 * @returns Whether parsing was successful.
 *
 */
bool	sphere_parse(char *str, size_t *parse_i)
{
	t_sphere	sphere;
	t_sphere	**ptr_to_next;

	sphere = (t_sphere){};
	skip_letters_and_trailing_spaces(str, parse_i);
	if (!vec4_parse(str, parse_i, &sphere.pos, true)
		|| !is_space(str[*parse_i - 1]))
		return (print_err("invalid sphere position"));
	sphere.radius /= 2;
	if (!sphere_parse_pt2(&sphere, str, parse_i))
		return (false);
	ptr_to_next = &dat()->elems.spheres;
	while (*ptr_to_next)
		ptr_to_next = &(*ptr_to_next)->next;
	*ptr_to_next = malloc(sizeof(t_sphere));
	if (!*ptr_to_next)
	{
		if (sphere.texture)
			mlx_delete_texture(sphere.texture);
		return (print_err("failed to allocate memory for sphere"));
	}
	**ptr_to_next = sphere;
	return (true);
}

static inline bool	sphere_parse_pt2(t_sphere *sphere,
						char *str, size_t *parse_i)
{
	if (!flt_parse(str, parse_i, &sphere->radius)
		|| sphere->radius < EPSILON || !is_space(str[*parse_i - 1]))
		return (print_err("invalid sphere diameter"));
	sphere->radius /= 2;
	if (!rgb_parse(str, parse_i, &sphere->color))
		return (print_err("invalid sphere color"));
	if (!optional_pattern_name_parse(str, parse_i, &sphere->pattern)
		&& !optional_asset_parse(str, parse_i, &sphere->texture))
		return (print_err("invalid sphere pattern name or texture"));
	if (!sphere->texture && !optional_pattern_color_parse(str, parse_i,
			sphere->pattern, &sphere->pattern_color))
		return (print_err("invalid sphere pattern color"));
	if (!is_end(str[*parse_i]))
	{
		if (!sphere->texture)
			return (print_err("invalid sphere data after pattern color"));
		mlx_delete_texture(sphere->texture);
		return (print_err("invalid sphere data after texture"));
	}
	return (true);
}
