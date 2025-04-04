#include "mini_rt.h"
#include <math.h>

void	vec3_print(t_vec3 vec)
{
	printf("x: %f, y: %f, z: %f\n", vec.x, vec.y, vec.z);
}

inline bool	vec3_near_zero(t_vec3 vec)
{
	return (fabsf(vec.x) < S && fabsf(vec.y) < S && fabsf(vec.z) < S);
}

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
