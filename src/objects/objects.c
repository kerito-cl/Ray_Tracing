#include "mini_rt.h"

bool	world_hit(t_info *info, t_ray *ray, t_hit_record *rec,
		t_interval *interval)
{
	int		i;
	float	t;
	bool	is_hit;

	i = 0;
	is_hit = false;
	while (i < info->obj_count)
	{
		if (info->obj[i].hit(&info->obj[i], ray, interval, rec))
		{
			if (rec->t < interval->max)
			{
				info->index = i;
				is_hit = true;
				interval->max = rec->t;
				rec->material->type_material = info->obj[i].type_material;
			}
		}
		i++;
	}
	return (is_hit);
}

bool	world_hit_shadow(t_info *info, t_ray *ray, t_hit_record *rec,
		t_interval *interval)
{
	int		i;
	float	t;
	bool	is_hit;

	i = 0;
	is_hit = false;
	while (i < info->obj_count)
	{
		if (info->obj[i].type_material != GLASS)
		{
			if (info->obj[i].hit(&info->obj[i], ray, interval, rec))
			{
				if (rec->t < interval->max)
				{
					if (info->index == i)
						info->hit_itself = true;
					else
						info->hit_itself = false;
					is_hit = true;
					interval->max = rec->t;
					rec->material->type_material = info->obj[i].type_material;
				}
			}
		}
		i++;
	}
	return (is_hit);
}
