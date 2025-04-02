#include "mini_rt.h"
#include <math.h>

inline t_vec3	vec3_mul_vec(t_vec3 vec, float scalar)
{
	return (vec3_new(vec.x * scalar, vec.y * scalar, vec.z * scalar));
}

inline t_vec3	vec3_div_vec(t_vec3 vec, float scalar)
{
	return (vec3_new(vec.x / scalar, vec.y / scalar, vec.z / scalar));
}

inline float	vec3_dot(t_vec3 vec1, t_vec3 vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

inline t_vec3	vec3_cross(t_vec3 vec1, t_vec3 vec2)
{
	return (vec3_new(vec1.y * vec2.z - vec1.z * vec2.y, vec1.z * vec2.x - vec1.x
			* vec2.z, vec1.x * vec2.y - vec1.y * vec2.x));
}

inline t_vec3	vec3_unit(t_vec3 vec)
{
	float	len;

	len = vec3_length(vec);
	return (vec3_div_vec(vec, len));
}
