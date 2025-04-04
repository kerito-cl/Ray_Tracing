#include "mini_rt.h"

static void	assign_str_to_vec(t_vec3 *vec3, char **cvec, bool *isvalid,
		bool if_rgb)
{
	char	*ptr;

	vec3->x = ft_strtof(cvec[0], &ptr);
	if (ptr[0] != 0)
		*isvalid = false;
	vec3->y = ft_strtof(cvec[1], &ptr);
	if (ptr[0] != 0)
		*isvalid = false;
	vec3->z = ft_strtof(cvec[2], &ptr);
	if (ptr[0] != 0 && ptr[0] != '\n')
		*isvalid = false;
	if (if_rgb)
	{
		vec3->x = vec3->x / 255;
		vec3->y = vec3->y / 255;
		vec3->z = vec3->z / 255;
	}
}

void	new_vec3_for_parsing(t_vec3 *vec3, char **cvec, bool *isvalid,
		bool if_rgb)
{
	if (!cvec[0] || !cvec[1] || !cvec[2] || cvec[3] != NULL
		|| cvec[0][0] == '\n')
	{
		freesplit(cvec);
		*isvalid = false;
		return ;
	}
	assign_str_to_vec(vec3, cvec, isvalid, if_rgb);
	if (*isvalid == false)
	{
		freesplit(cvec);
		return ;
	}
	if (cvec != NULL)
		freesplit(cvec);
}

t_point	ray_at(t_ray *ray, double t)
{
	t_point	point;

	point = vec3_new(ray->orig.x + t * ray->direc.x, ray->orig.y + t
			* ray->direc.y, ray->orig.z + t * ray->direc.z);
	return (point);
}

void	set_face_normal(t_ray r, t_vec3 outward_normal, t_hit_record *rec)
{
	rec->front_face = vec3_dot(r.direc, outward_normal) < 0;
	if (rec->front_face)
		rec->normal = outward_normal;
	else
		rec->normal = vec3_flip_minus(outward_normal);
}

float	clamp(float n, float min, float max)
{
	if (n < min)
		return (min);
	if (n > max)
		return (max);
	return (n);
}
