#include "mini_rt.h"

inline float	vec3_length(t_vec3 vec)
{
	return (sqrt(vec3_length_squared(vec)));
}

inline t_vec3	vec3_div(float number, t_vec3 vec)
{
	return (vec3_new(number / vec.x, number / vec.y, number / vec.z));
}

inline t_vec3	vec3_min(t_vec3 vec1, t_vec3 vec2)
{
	return (vec3_new(fminf(vec1.x, vec2.x), fminf(vec1.y, vec2.y), fminf(vec1.z,
				vec2.z)));
}

inline t_vec3	vec3_max(t_vec3 vec1, t_vec3 vec2)
{
	return (vec3_new(fmaxf(vec1.x, vec2.x), fmaxf(vec1.y, vec2.y), fmaxf(vec1.z,
				vec2.z)));
}
