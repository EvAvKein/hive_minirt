/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:52:35 by ekeinan           #+#    #+#             */
/*   Updated: 2025/06/17 10:43:28 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdbool.h>
# include "libft_plus.h"

# define WINDOW_WIDTH	1024
# define WINDOW_HEIGHT	1024

typedef float	t_flt;

/* ------------------------------------------------------------------- colors */

// Endiannes, consider removing later (unclear if conditional compilation is ok)
# if 1

typedef struct s_channels
{
	uint8_t	a;
	uint8_t	b;
	uint8_t	g;
	uint8_t	r;
}			t_channels;

enum e_channel_type
{
	A,
	B,
	G,
	R,
};

# else

typedef struct s_channels
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;
}			t_channels;

enum e_channel_type
{
	R,
	G,
	B,
	A,
};

# endif

typedef union u_8bit_color
{
	uint32_t	rgba;
	t_channels	channel;
	uint8_t		ch[4];
}				t_8bit_color;

typedef struct s_float_color
{
	float	r;
	float	g;
	float	b;
	float	a;
}			t_float_color;

typedef struct s_color
{
	t_8bit_color	bit;
	t_float_color	flt;
}					t_color;

/* ----------------------------------------------------- vectors and matrices */

typedef struct s_axis
{
	t_flt	x;
	t_flt	y;
	t_flt	z;
	t_flt	w;
}			t_axis;

typedef union u_vec4
{
	t_flt	_[4];
	t_axis	axis;
}			t_vec4;

typedef struct t_m4x4
{
	t_flt	_[4][4];
}			t_m4x4;

/* ------------------------------------------------------------ scene objects */

typedef struct s_camera
{
	t_vec4	pos;
	t_vec4	orientation;
	uint8_t	fov;
}			t_camera;

typedef struct s_ambient_light
{
	t_flt	brightness;
	t_color	color;
}			t_ambient_light;

typedef struct s_light
{
	t_vec4			pos;
	t_flt			brightness;
	// t_color	color; // bonus
	struct s_light	*next;
}					t_light;

typedef struct s_sphere
{
	t_vec4			pos;
	t_flt			radius;
	t_color			color;
	struct s_sphere	*next;
}					t_sphere;

typedef struct s_plane
{
	t_vec4			pos;
	t_vec4			orientation;
	t_color			color;
	struct s_plane	*next;
}					t_plane;

typedef struct s_cylinder
{
	t_vec4				pos;
	t_vec4				orientation;
	t_flt				diam;
	t_flt				height;
	t_color				color;
	struct s_cylinder	*next;
}						t_cylinder;

typedef struct s_elems
{
	t_camera		camera;
	t_ambient_light	ambient_light;
	t_light			*lights;
	t_sphere		*spheres;
	t_plane			*planes;
	t_cylinder		*cylinders;
}					t_elems;

typedef struct s_data
{
	t_elems	elems;
	uint8_t	pixels[WINDOW_HEIGHT][WINDOW_WIDTH];
}			t_data;

t_data	*get_data(void);

#endif
