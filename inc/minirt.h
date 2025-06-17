/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:52:35 by ekeinan           #+#    #+#             */
/*   Updated: 2025/06/17 10:20:47 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdbool.h>
# include "libft_plus.h"

typedef float	t_flt;

typedef	t_vec4;
typedef	t_color;

typedef struct s_camera {
	t_vec4	pos;
	t_vec4	orientation;
	uint8_t	fov;
}			t_camera;

typedef struct s_ambient_light {
	t_flt	brightness;
	t_color	color;
}			t_ambient_light;

typedef struct s_light {
	t_vec4	pos;
	t_flt	brightness;
	// t_color	color; // bonus
}			t_light;

typedef struct s_sphere {
	t_vec4	pos;
	t_flt	diam;
	t_color	color;
}			t_sphere;

typedef struct s_plane {	
	t_vec4	pos;
	t_vec4	orientation;
	t_color	color;
}			t_plane;

typedef struct s_cylinder {	
	t_vec4	pos;
	t_vec4	orientation;
	t_flt	diam;
	t_flt	height;
	t_color	color;
}			t_cylinder;

typedef struct s_elems {	
	t_camera		camera;
	t_ambient_light	ambient_light;
	t_light			*lights;
	t_sphere		*spheres;
	t_plane			*planes;
	t_cylinder		*cylinders;
}				t_elems;

typedef struct s_data {
	t_elems	elems;
}			t_data;

t_data	*get_data(void);

#endif
