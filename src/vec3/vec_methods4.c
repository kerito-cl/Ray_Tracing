#include "mini_rt.h"
#include <math.h>

t_vec3	vec3_random(void)
{
	return (vec3_new(RANDOM_FLOAT, RANDOM_FLOAT, RANDOM_FLOAT));
}

t_vec3	vec3_random_range(float min, float max)
{
	return (vec3_new(RANDOM_FLOAT_RANGE(min, max), RANDOM_FLOAT_RANGE(min, max),
			RANDOM_FLOAT_RANGE(min, max)));
}

t_vec3	vec3_random_unit_vector(void)
{
	t_vec3	vec;
	float	len_sq;

	while (1)
	{
		vec = vec3_random_range(-1, 1);
		len_sq = vec3_length_squared(vec);
		if (len_sq > 1e-12 && len_sq <= 1)
			return (vec3_div_vec(vec, sqrtf(len_sq)));
	}
}

t_vec3	vec3_random_on_hemisphere(t_vec3 normal)
{
	t_vec3	random;

	random = vec3_random_unit_vector();
	if (vec3_dot(random, normal) > 0)
		return (random);
	return (vec3_flip_minus(random));
}

t_vec3 vec3_copy(t_vec3 vec)
{
    return vec3_new(vec.x, vec.y, vec.z);
}