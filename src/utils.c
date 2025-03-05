
#include "mini_rt.h"

void	new_vec3_for_parsing(t_vec3 *vec3, char **cvec, bool *isvalid,
		bool if_rgb)
{
	if (!cvec[0] || !cvec[1] || !cvec[2] || cvec[3] != NULL)
	{
		freesplit(cvec);
		*isvalid = false;
		return ;
	}
	vec3->x = ft_strtof(cvec[0], NULL);
	vec3->y = ft_strtof(cvec[1], NULL);
	vec3->z = ft_strtof(cvec[2], NULL);
	if (if_rgb)
	{
		vec3->x = ft_strtof(cvec[0], NULL) / 255;
		vec3->y = ft_strtof(cvec[1], NULL) / 255;
		vec3->z = ft_strtof(cvec[2], NULL) / 255;
	}
	if (cvec != NULL)
		freesplit(cvec);
}

t_point	ray_at(t_ray *ray, double t)
{
	t_point point;

	point = vec3_new(
        ray->orig.x + t * ray->direc.x, 
        ray->orig.y + t * ray->direc.y, 
        ray->orig.z + t * ray->direc.z);
	return (point);
}
void set_face_normal(t_ray r, t_vec3 outward_normal, t_hit_record *rec)
{
    rec->front_face = vec3_dot(r.direc, outward_normal) < 0;
    if (rec->front_face)
        rec->normal = outward_normal;
    else
        rec->normal = vec3_flip_minus(outward_normal);
}