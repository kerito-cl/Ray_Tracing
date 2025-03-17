#include "mini_rt.h"

t_color	vec3_sky(void)
{
	return (vec3_new(0.01960784313f, 0.01960784313f, 1.0f));
}

bool	vec3_near_black(t_color color)
{
	return (color.x < 0.001f && color.y < 0.001f && color.z < 0.001f);
}

t_color vec3_black(void)
{
	return (vec3_new(0, 0, 0));
}

t_color	vec3_avoid_overflow(t_vec3 color)
{
	return (vec3_new(fmaxf(color.x, 1), fmaxf(color.y, 1), fmaxf(color.z, 1)));
}
