/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:26:27 by mquero            #+#    #+#             */
/*   Updated: 2025/04/09 13:27:30 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARS_H
# define VARS_H

# include "mini_rt.h"

typedef struct s_sp_hit_vars
{
	t_vec3			oc;
	t_vec3			outward_normal;
	float			a;
	float			b;
	float			c;
	float			t[2];
}					t_sp_hit_vars;

typedef struct s_get_light_vars
{
	t_ray			*cam_ray;
	t_ray			shadow_ray;
	t_hit_record	*cam_rec;
	t_hit_record	shadow_rec;
	t_interval		interval;
}					t_get_light_vars;

typedef struct s_hit_cy_vars
{
	t_vec3			x;
	t_vec3			v;
	t_vec3			hit_vec;
	float			a;
	float			b;
	float			c;
	float			d_dot;
	float			x_dot;
	float			m;
	float			t[2];
}					t_hit_cy_vars;

typedef struct s_hit_cone_vars
{
	t_vec3			oc;
	t_vec3			d_proj;
	t_vec3			oc_proj;
	t_vec3			p_base;
	float			cos2;
	float			d_dot_n;
	float			oc_dot_n;
	float			a;
	float			b;
	float			c;
	float			m;
	float			t[2];
}					t_hit_cone_vars;

typedef struct s_hit_box_vars
{
	t_vec3			inv_d;
	t_vec3			tmin;
	t_vec3			tmax;
	t_vec3			t0;
	t_vec3			t1;
	float			tminf;
	float			tmaxf;

}					t_hit_box_vars;

// These are helper properties, and the value is assigned when init the camera.
//
// look_at: the center point of the image plane.
//
// vfov: the Vertical Field of View, means the angle of viewpoint,
//       the value is affected by focal which is the distance
//       from point of camera to point of image, and the size of image.
//       vfov = 2 * arctan((sizeof_image_plane / 2) / distance)
//
// vup: The up direction in world space (Y-axis direction).
//      It normally points to (0, 1, 0),
//    	representing the world's upward direction.
//
// v: the upward unit vector in the image plane, the direction to up.
//    when the camara is normally placed, the u is 0, 1, 0.
//    = unit(cross(w, u));
//
// aspect_ratio: the aspect ratio of image plane.
//
// focal_length: the distance from the camera's observation point 
// to the image plane.
//
// top_left: the top-left pixel of the image plane.
//
// viewport_height: the height of image plane in world space coordinator.
// viewport_width: the width of the image plane world space coordinator.
//
// viewpoint_u: a vector of the width of the image plane. u * viewport_width.
// viewpoint_v: a vector of the height of the image plane. v * viewport_height.
// combines both length and direction, as well as a line.
//
// dist: the direction from the observation point to the center of image plane.
// right: the camera's right vector, just a temp variable.
typedef struct s_camera_init_vars
{
	t_point			look_at;
	t_vec3			right;
	t_vec3			vup;
	t_vec3			v;
	t_vec3			viewport_u;
	t_vec3			viewport_v;
	t_point			top_left;
	float			focal_length;
	float			viewport_height;
	float			viewport_width;
	float			aspect_ratio;
	float			vfov;
}					t_camera_init_vars;

#endif