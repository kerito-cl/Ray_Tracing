#include "mini_rt.h"

bool	world_hit(t_info *info, t_ray *ray, t_hit_record *rec, t_interval *interval)
{
	int i;
	float t;
	bool is_hit;

	i = 0;
	is_hit = false;
	while (i < info->obj_count)
	{
		if (info->obj[i].hit(&info->obj[i], ray, interval, rec))
		{
			if (rec->t < interval->max)
			{
				is_hit = true;
				interval->max = rec->t;
			}
		}
		i++;
	}
	return (is_hit);
}
