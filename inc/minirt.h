/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:52:35 by ekeinan           #+#    #+#             */
/*   Updated: 2025/07/11 10:19:07 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdbool.h>		// bool
# include <limits.h>		// LLONG_MAX
# include <fcntl.h>			// open()
# include <math.h>			// pow(), fabs()
# include <float.h>			// FLT_MAX & DBL_MAX
# include <stdio.h>			// printf()
# include "libft_plus.h"
# include "MLX42.h"
# include "settings.h"

# define RADIANS_PER_DEGREE	0.0174532925
# define DEGREES_PER_RADIAN	57.2957795

typedef float	t_flt;

typedef enum e_error
{
	ERROR_MLX_INIT = 3,
	ERROR_MLX_NEW_IMAGE,
	ERROR_MLX_IMAGE_TO_WINDOW,
	ERROR_PROBLEM_WITH_RESOLUTION,
	ERROR_ALLOC,
}	t_error;

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

typedef struct t_m3x3
{
	t_flt	_[3][3];
}			t_m3x3;

typedef struct t_m2x2
{
	t_flt	_[2][2];
}			t_m2x2;

// vectors/vectors_01.c
t_flt			vec_len(t_vec4 vec);
t_vec4			unit_vec(t_vec4 vec);
t_vec4			scaled_vec(t_vec4 vec, t_flt scalar);
t_vec4			vector(t_flt x, t_flt y, t_flt z);
t_vec4			position(t_flt x, t_flt y, t_flt z);

// vectors/vectors_02.c
t_flt			dot(t_vec4 v1, t_vec4 v2);
t_vec4			vec_sum(t_vec4 v1, t_vec4 v2);
t_vec4			vec_sub(t_vec4 v1, t_vec4 v2);
t_vec4			transformed_vec(t_vec4 vec, t_m4x4 t);
void			print_vec(t_vec4 vec);

// matrices/matrices_01.c
t_m4x4			mult_m4x4(t_m4x4 m4x4_1, t_m4x4 m4x4_2);
t_m4x4			scaled_m4x4(t_m4x4 m4x4, t_flt scalar);
void			print_m4x4(t_m4x4 m4x4);

// matrices/matrices_02.c
t_m2x2			sub_m3x3(t_m3x3 m3x3, size_t row, size_t col);
t_m3x3			sub_m4x4(t_m4x4 m4x4, size_t row, size_t col);
t_flt			det_m2x2(t_m2x2 m2x2);
t_flt			det_m3x3(t_m3x3 m3x3);
t_flt			det_m4x4(t_m4x4 m4x4);

// matrices/matrices_03.c
t_m4x4			identity_m4x4(void);
t_m4x4			transpose_m4x4(t_m4x4 m4x4);
t_flt			cofactor_m4x4(t_m4x4 m4x4, size_t row, size_t col);
t_m4x4			inverse_m4x4(t_m4x4 m4x4);

// matrices/transforms_01.c
t_m4x4			translation_m4x4(t_vec4 vec);
t_m4x4			scaling_m4x4(t_vec4 vec);
t_m4x4			x_rotation_m4x4(t_flt rad);
t_m4x4			y_rotation_m4x4(t_flt rad);
t_m4x4			z_rotation_m4x4(t_flt rad);

/* ---------------------------------------------------------------- MATERIALS */

typedef struct s_material
{
	t_vec4	color;
	t_flt	ambient;
	t_flt	diffuse;
	t_flt	specular;
	t_flt	shininess;
}			t_material;

typedef struct s_light\
				t_light;

typedef struct s_phong_helper
{
	t_material const	*mat;
	t_light const		*light;
	t_vec4				pos;
	t_vec4				normal;
	t_vec4				to_cam;
	t_vec4				to_light;
	t_vec4				from_light;
	t_vec4				effective_color;
	t_vec4				ambient;
	t_vec4				diffuse;
	t_vec4				specular;
	t_vec4				combined;
	t_vec4				ref;
	t_vec4				scaled_light;
	t_flt				surface_light_alignment;
	t_flt				camera_reflection_alignment;
}						t_phong_helper;

// objects/materials_01.c
t_material		material(t_flt amb, t_flt diff, t_flt spec, t_flt shiny);
t_material		default_material(void);

/* ----------------------------------------------------------------- LIGHTING */

t_color			let_there_be_light(t_phong_helper *p);

/* ------------------------------------------------------------ SCENE OBJECTS */

typedef enum e_obj_type
{
	UNKNOWN,
	CAMERA,
	AMBIENT_LIGHT,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
}	t_obj_type;

typedef struct s_camera
{
	t_vec4	pos;
	t_vec4	orientation;
	uint8_t	fov;
	t_m4x4	transform;
	t_m4x4	inverse;
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
	t_m4x4			transform;
	t_m4x4			inverse;
	struct s_light	*next;
}					t_light;

typedef struct s_sphere
{
	t_vec4			pos;
	t_flt			radius;
	t_color			color;
	t_m4x4			transform;
	t_m4x4			inverse;
	t_material		material;
	struct s_sphere	*next;
}					t_sphere;

typedef struct s_plane
{
	t_vec4			pos;
	t_vec4			orientation;
	t_color			color;
	t_m4x4			transform;
	t_m4x4			inverse;
	struct s_plane	*next;
}					t_plane;

typedef struct s_cylinder
{
	t_vec4				pos;
	t_vec4				orientation;
	t_flt				diam;
	t_flt				height;
	t_color				color;
	t_m4x4				transform;
	t_m4x4				inverse;
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

/* --------------------------------------------------------------------- RAYS */

typedef struct s_ray_x_obj
{
	t_obj_type		obj_type;
	void			*obj;
	t_flt			t;
}					t_ray_x_obj;

typedef struct s_ray_x_objs
{
	size_t		count;
	t_ray_x_obj	_[2];
}			t_ray_x_objs;

typedef struct s_ray_x_obj_array
{
	size_t		capacity;
	size_t		idx;
	t_ray_x_obj	*_;
}				t_ray_x_obj_array;

typedef struct s_ray
{
	t_vec4				dir;
	t_vec4				orig;
	t_ray_x_obj_array	intersections;
}						t_ray;

/* -------------------------------------------------------------------------- */

typedef struct s_pixel_grid
{
	t_flt	fov_h;
	t_flt	fov_v;
	t_flt	width;
	t_flt	height;
	t_flt	pixel_width;
}			t_pixel_grid;

typedef struct s_data
{
	t_elems			elems;
	t_pixel_grid	pixel_grid;
	t_ray			*pixel_rays;
	size_t			pixel_count;
	size_t			object_count;
	size_t			intersection_count;
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_error			error;
}					t_data;

t_data			*get_data(void);

void			image_to_file(const char *bmp_file_path);

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
// rays/rays_01.c
t_ray			transformed_ray(t_ray ray, t_m4x4 transform);
t_ray			inverse_transformed_ray(t_ray ray, t_m4x4 transform);
t_vec4			reflection(t_vec4 vec, t_vec4 normal);

// objects/transform_initialization.c
void			init_transforms(void);

/* ------------------------------------------------------------ INTERSECTIONS */

// objects/sphere_intersection.c
t_ray_x_objs	ray_x_sphere(t_ray ray, t_sphere *sp);
t_ray_x_obj		hit(t_ray_x_objs intersections);
t_vec4			sphere_normal_at(t_sphere sp, t_vec4 world_pos);

// intersections/intersections_01.c
void			*xcalloc(size_t nmemb, size_t size);
void			xinit_ray_intersections(t_ray *ray);
void			xadd_intersection(t_ray *ray, t_ray_x_obj intersection);

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
void			keyhook(mlx_key_data_t key_data, void *param);

/* -------------------------------------------------------------------- UTILS */

typedef struct s_quad
{
	t_flt	a;
	t_flt	b;
	t_flt	c;
	t_flt	discr;
}			t_quad;

// utils/utils_01.c
t_flt			to_radians(t_flt degrees);
t_flt			to_degrees(t_flt radians);
bool			floats_are_equal(t_flt flt1, t_flt flt2);
bool			vecs_are_equal(t_vec4 vec1, t_vec4 vec2);
bool			in_front_of_camera(t_camera cam, t_vec4 vec);

// utils/utils_02.c
void			write_pixel_rays_to_file(const char *str);
t_quad			solve_sphere_quadratic(t_ray ray, t_sphere sp);
t_color			vec4_to_color(t_vec4 vec);
t_color			normal_to_color(t_vec4 normal);

/* -------------------------------------------------------------------- TESTS */

void			single_sphere_test(void);

/* ------------------------------------------------------ IMAGE FILE CREATION */

/**
 *
 * Packs members of the structs declared inside by the provided segment size.
 * With a segment size of one, it doesn't ever add padding between members.
 *
 * This is necessary for bitmap files' header formatting.
 *
 */
# pragma pack(push, 1)

/**
 *
 * Based on `BITMAPFILEHEADER` (from `<wingdi.h>`)
 *
 * For more info, see:
 * learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapfileheader
 *
 */
typedef struct s_bmp_fileheader
{
	uint16_t	file_type;
	uint32_t	file_size;
	uint16_t	reserved1;
	uint16_t	reserved2;
	uint32_t	bitmap_offset;
}				t_bmp_fileheader;

/**
 *
 * Based on `BITMAPINFOHEADER` (from `<wingdi.h>`)
 *
 * For more info, see:
 * learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfoheader
 *
 */
typedef struct s_bmp_infoheader
{
	uint32_t	size;
	uint32_t	width;
	uint32_t	height;
	uint16_t	color_planes;
	uint16_t	bits_per_pixel;
	uint32_t	compression;
	uint32_t	size_of_bitmap;
	int32_t		horizontal_ppm;
	int32_t		vertical_ppm;
	uint32_t	colors_used;
	uint32_t	colors_important;
}				t_bmp_infoheader;

# pragma pack(pop)

#endif
