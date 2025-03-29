#include "mini_rt.h"
#include <math.h>

t_vec3	vec3_new(float x, float y, float z)
{
	t_vec3 vec;

	vec.simd = _mm_set_ps(0.0f, z, y, x);
	return vec;
}

t_vec3	vec3_flip_minus(t_vec3 vec)
{
	t_vec3 result;

	result.simd = _mm_mul_ps(vec.simd, _mm_set1_ps(-1.0f));
	return result;
}

float	vec3_length_squared(t_vec3 vec)
{
	__m128 mul;
	__m128 shuf;
	__m128 sums;

	mul = _mm_mul_ps(vec.simd, vec.simd);
	shuf = _mm_movehl_ps(mul, mul);
	sums = _mm_add_ps(mul, shuf); 
	shuf = _mm_shuffle_ps(sums, sums, 1);
	sums = _mm_add_ss(sums, shuf);
	return _mm_cvtss_f32(sums);
}

float	vec3_length(t_vec3 vec)
{
	return sqrtf(vec3_length_squared(vec));
}
