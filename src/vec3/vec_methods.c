#include "mini_rt.h"
#include <math.h>

t_vec3	vec3_new(float x, float y, float z)
{
	t_vec3	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

float    vec_length(t_vec3 vec1)
{
    float  x;
    float  y;
    float  z;

    x = vec1.x * vec1.x;
    y = vec1.y * vec1.y;
    z = vec1.z * vec1.z;
    return (sqrtf(x + y + z));
}

void	vec3_normalize(t_vec3 *vec)
{
	float	inverse;

	inverse = 1 / vec_length(*vec);
	if (inverse == 0)
		return ;
	vec->x = vec->x * inverse;
	vec->y = vec->y * inverse;
	vec->z = vec->z * inverse;
}

t_vec3	vec3_flip_minus(t_vec3 vec)
{
	return (vec3_new(-vec.x, -vec.y, -vec.z));
}

float	vec3_length_squared(t_vec3 vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

float	vec3_length(t_vec3 vec)
{
	return (sqrt(vec3_length_squared(vec)));
}
