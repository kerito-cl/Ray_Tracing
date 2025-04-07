#include "mini_rt.h"

t_color	vec3_sky(void)
{
	return (vec3_new(0.13f, 0.13f, 0.13f));
}

bool	vec3_near_black(t_color color)
{
	return (color.x < 0.001f && color.y < 0.001f && color.z < 0.001f);
}

t_color	vec3_black(void)
{
	return (vec3_new(0, 0, 0));
}
