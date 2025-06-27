/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:52:35 by ekeinan           #+#    #+#             */
/*   Updated: 2025/06/26 15:19:53 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdbool.h>		// bool
# include <limits.h>		// LLONG_MAX
# include <fcntl.h>			// open()
# include <math.h>			// pow()
# include <float.h>			// FLT_MAX & DBL_MAX
# include <stdio.h>			// printf()
# include "libft_plus.h"
# include "MLX42.h"

# define RES_X	1280	// 3840	1920
# define RES_Y	720		// 2160	1080

# define RADIANS_PER_DEGREE	0.0174532925
# define DEGREES_PER_RADIAN	57.2957795
# define EPSILON			0.00001

typedef float	t_flt;

enum e_error
{
	ERROR_MLX_INIT = 3,
	ERROR_MLX_NEW_IMAGE,
	ERROR_MLX_IMAGE_TO_WINDOW,
	ERROR_PROBLEM_WITH_RESOLUTION,
	ERROR_ALLOC,
};

/* ------------------------------------------------------------------- COLORS */

// Endiannes, consider removing later (unclear if conditional compilation is ok)
# if 0

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
	uint8_t		_[4];
}				t_8bit_color;

typedef struct s_float_color
{
	t_flt	r;
	t_flt	g;
	t_flt	b;
	t_flt	a;
}			t_float_color;

typedef struct s_color
{
	t_8bit_color	bit;
	t_float_color	flt;
}					t_color;

t_float_color	color_8bit_to_float(t_8bit_color c);
t_8bit_color	color_float_to_8bit(t_float_color c);
t_float_color	lerp_color(t_float_color c1, t_float_color c2, float amount);

/* ----------------------------------------------------- VECTORS AND MATRICES */

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

t_flt			vector_len(t_vec4 const *vec);
t_vec4			new_unit_vector(t_vec4 const *vec);
t_vec4			*normalize_vector(t_vec4 *vec);
void			print_vec(t_vec4 const *vec);

t_m4x4			*multiply_matrix_in_place(t_m4x4 const *mult, t_m4x4 *mat);
t_m4x4			new_mult_matrix(const t_m4x4 *mat1, const t_m4x4 *mat2);
t_m4x4			*scale_matrix_in_place(t_flt scalar, t_m4x4 *mat);
t_m4x4			new_scaled_matrix(t_flt scalar, t_m4x4 const *mat);

/* ------------------------------------------------------------ SCENE OBJECTS */

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
	t_color			color;
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
	t_camera		*camera;
	t_ambient_light	*ambient_light;
	t_light			*lights;
	t_sphere		*spheres;
	t_plane			*planes;
	t_cylinder		*cylinders;
}					t_elems;

typedef struct s_data
{
	t_elems			elems;
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_vec4			*pixel_rays;
	size_t			pixel_count;
	enum e_error	error;
}			t_data;

t_data			*get_data(void);

bool			print_err(char *error);

bool			parse_scene(char *file_path);
bool			is_space(char c);
void			skip_spaces(char *str, size_t *parse_i);
void			skip_letters_and_trailing_spaces(char *str, size_t *parse_i);
bool			in_flt_range(t_flt checked, t_flt min, t_flt max);
bool			is_normalized_vec(t_vec4 vec);

bool			flt_parse(char *str, size_t *parse_i, t_flt *dest);
bool			uint8_parse(char *str, size_t *parse_i, uint8_t *dest);

bool			rgb_parse(char *str, size_t *parse_i, t_8bit_color *dest);
bool			vec4_parse(char *str, size_t *parse_i, t_vec4 *dest,
					bool is_point);

bool			ambient_light_parse(char *str, size_t *parse_i);
bool			camera_parse(char *str, size_t *parse_i);
bool			light_parse(char *str, size_t *parse_i);
bool			sphere_parse(char *str, size_t *parse_i);
bool			plane_parse(char *str, size_t *parse_i);
bool			cylinder_parse(char *str, size_t *parse_i);

/* --------------------------------------------------------- MEMORY & CLEANUP */

void			free_data(void);
void			dealloc_lights(t_light *light);
void			dealloc_spheres(t_sphere *sphere);
void			dealloc_planes(t_plane *plane);
void			dealloc_cylinders(t_cylinder *cylinder);

/* -------------------------------------------------------------- BACKGROUNDS */

void			set_horizontal_gradient(mlx_image_t *img,
					t_float_color colors[2]);
void			set_vertical_gradient(mlx_image_t *img,
					t_float_color colors[2]);
void			set_uv(mlx_image_t *img);

/* ---------------------------------------------- DATA SETUP & INITIALIZATION */

void			setup_pixel_rays(void);
bool			data_init_successful(void);

/* -------------------------------------------------------------------- UTILS */

typedef struct s_pixel_grid
{
	t_flt	fov_h;
	t_flt	fov_v;
	t_flt	width;
	t_flt	height;
	t_flt	pixel_width;
}			t_pixel_grid;

t_flt			to_radians(t_flt degrees);
t_flt			to_degrees(t_flt radians);
bool			floats_are_equal(t_flt flt1, t_flt flt2);
bool			vecs_are_equal(t_vec4 const *vec1, t_vec4 const *vec2);

#endif
