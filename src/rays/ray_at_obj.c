/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_at_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:26:58 by ekeinan           #+#    #+#             */
/*   Updated: 2025/08/13 17:12:53 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	cast_ray_at_spheres(t_ray *ray,
				t_sphere *spheres, void const *obj_ignore);
static void	cast_ray_at_planes(t_ray *ray,
				t_plane *planes, void const *obj_ignore);
static void	cast_ray_at_cylinders(t_ray *ray,
				t_cylinder *cylinders, void const *obj_ignore);
static void	cast_ray_at_triangles(t_ray *ray,
				t_triangle *triangles, void const *obj_ignore);

/**
 *	checks if the provided ray intersects with any objects,
 *	adding any such intersections to the ray's array
 */
void	cast_ray_at_objs(t_ray *ray, t_elems *elems, void const *obj_ignore)
{
	cast_ray_at_spheres(ray, elems->spheres, obj_ignore);
	cast_ray_at_planes(ray, elems->planes, obj_ignore);
	cast_ray_at_cylinders(ray, elems->cylinders, obj_ignore);
	cast_ray_at_triangles(ray, elems->triangles, obj_ignore);
	cast_ray_at_cones(ray, elems->cones, obj_ignore);
}

/**
 *	checks if the provided ray intersects with any spheres,
 *	adding any such intersections to the ray's array
 */
static void	cast_ray_at_spheres(t_ray *ray,
				t_sphere *spheres, void const *obj_ignore)
{
	t_ray_x_objs	rxos;
	t_ray_x_obj		rxo;
	t_sphere		*sphere;

	sphere = spheres;
	while (sphere)
	{
		if (sphere == obj_ignore)
		{
			sphere = sphere->next;
			continue ;
		}
		rxos = ray_x_sphere(*ray, sphere);
		rxo = hit(rxos);
		if (rxo.t > EPSILON && rxo.t < ray->closest_hit.t)
			ray->closest_hit = rxo;
		sphere = sphere->next;
	}
}

/**
 *	checks if the provided ray intersects with any planes,
 *	adding any such intersections to the ray's array
 */
static void	cast_ray_at_planes(t_ray *ray,
					t_plane *planes, void const *obj_ignore)
{
	t_ray_x_obj	rxo;
	t_plane		*plane;

	plane = planes;
	while (plane)
	{
		if (plane == obj_ignore)
		{
			plane = plane->next;
			continue ;
		}
		rxo = ray_x_plane(*ray, plane);
		if (rxo.t > EPSILON && rxo.t < ray->closest_hit.t)
			ray->closest_hit = rxo;
		plane = plane->next;
	}
}

/**
 *	Checks if the provided ray intersects with any cylinders,
 *	adding any such intersections to the ray's array
 */
static void	cast_ray_at_cylinders(t_ray *ray,
					t_cylinder *cylinders, void const *obj_ignore)
{
	t_ray_x_obj		rxo;
	t_cylinder		*cylinder;

	cylinder = cylinders;
	while (cylinder)
	{
		if (cylinder == obj_ignore)
		{
			cylinder = cylinder->next;
			continue ;
		}
		rxo = ray_hit_cylinder(*ray, cylinder);
		if (rxo.t > EPSILON && rxo.t < ray->closest_hit.t)
			ray->closest_hit = rxo;
		cylinder = cylinder->next;
	}
}

/**
 *	Checks if the provided ray intersects with any triangles,
 *	adding any such intersections to the ray's array
 */
static void	cast_ray_at_triangles(t_ray *ray,
					t_triangle *triangles, void const *obj_ignore)
{
	t_ray_x_obj		rxo;
	t_triangle		*triangle;

	triangle = triangles;
	while (triangle)
	{
		if (triangle == obj_ignore)
		{
			triangle = triangle->next;
			continue ;
		}
		rxo = ray_x_triangle(*ray, triangle);
		if (rxo.t > EPSILON && rxo.t < ray->closest_hit.t)
			ray->closest_hit = rxo;
		triangle = triangle->next;
	}
}
