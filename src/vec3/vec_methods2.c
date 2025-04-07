#include "mini_rt.h"
#include <math.h>

inline t_vec3	vec3_add_vecs(t_vec3 vec1, t_vec3 vec2)
{
	return (vec3_new(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z));
}

inline t_vec3	vec3_sub_vecs(t_vec3 vec1, t_vec3 vec2)
{
	return (vec3_new(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z));
}

inline t_vec3	vec3_mul_vecs(t_vec3 vec1, t_vec3 vec2)
{
	return (vec3_new(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z));
}

inline t_vec3	vec3_div(float number, t_vec3 vec)
{
	return (vec3_new(number / vec.x, number / vec.y, number / vec.z));
}
