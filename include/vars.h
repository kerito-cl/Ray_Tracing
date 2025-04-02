#ifndef VARS_H
# define VARS_H

# include "mini_rt.h"

typedef struct s_sp_hit_vars
{
	t_vec3			oc;
	float			a;
	float			b;
	float			c;
	float			t[2];
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
	t_vec3			hit_vec;
	float			t[2];
	float			a;
	float			b;
	float			c;
	float			d_dot;
	float			x_dot;
	float			m;
}					t_hit_cy_vars;


typedef struct s_hit_cone_vars
{
	t_vec3			oc;
	float			cos2;
	float			d_dot_n;
	float			oc_dot_n;
	t_vec3			d_proj;
	t_vec3			oc_proj;
	float			t[2];
	float			a;
	float			b;
	float			c;
	float			m;
	t_vec3			p_base;

} t_hit_cone_vars;

typedef struct s_hit_box_vars
{
	t_vec3		inv_d;
	t_vec3		t_min;
	t_vec3		t_max;
	t_vec3		t0;
	t_vec3		t1;
	float		tminf;
	float		tmaxf;

}  t_hit_box_vars;

#endif