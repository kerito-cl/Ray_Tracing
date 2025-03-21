#ifndef VARS_H
# define VARS_H

# include "mini_rt.h"

typedef struct s_sp_hit_vars
{
	t_vec3			oc;
	float			a;
	float			h;
	float			c;
	float			discriminant;
	float			sqrtd;
	float			root;
	t_vec3			temp;
	t_vec3			outward_normal;
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
	float			t0;
	float			t1;
	float			a;
	float			b;
	float			c;
	float			d_dot;
	float			x_dot;
	float			m;
}					t_hit_cy_vars;

#endif