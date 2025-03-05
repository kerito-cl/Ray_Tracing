#ifndef VARS_H
# define VARS_H

# include "mini_rt.h"

typedef struct s_sp_hit_vars
{
	t_vec3	oc;
	float	a;
	float	h;
	float	c;
	float	discriminant;
	float	sqrtd;
	float	root;
	t_vec3	temp;
	t_vec3	outward_normal;
}			t_sp_hit_vars;

#endif