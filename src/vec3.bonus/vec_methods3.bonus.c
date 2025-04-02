#include "mini_rt.h"
#include <math.h>

t_vec3	vec3_mul_vec(t_vec3 vec, float scalar)
{
	t_vec3 result;

	result.simd = _mm_mul_ps(vec.simd, _mm_set1_ps(scalar));
	return result;
}

t_vec3	vec3_div_vec(t_vec3 vec, float scalar)
{
	t_vec3 result;

	result.simd = _mm_div_ps(vec.simd, _mm_set1_ps(scalar));
	return result;
}

float	vec3_dot(t_vec3 vec1, t_vec3 vec2)
{
	__m128 mul; 
	__m128 shuf; 
	__m128 sum; 

	mul = _mm_mul_ps(vec1.simd, vec2.simd);
	shuf = _mm_movehl_ps(mul, mul);
	sum = _mm_add_ps(mul, shuf);
	shuf = _mm_shuffle_ps(sum, sum, 1);
	sum = _mm_add_ss(sum, shuf);
	return _mm_cvtss_f32(sum);
}

t_vec3	vec3_cross(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3 result;
	__m128 a_yzx;
	__m128 b_zxy;
	__m128 a_zxy;
	__m128 b_yzx;


	a_yzx = _mm_shuffle_ps(a.simd, a.simd, _MM_SHUFFLE(3, 0, 2, 1));
	b_zxy = _mm_shuffle_ps(b.simd, b.simd, _MM_SHUFFLE(3, 1, 0, 2));
	a_zxy = _mm_shuffle_ps(a.simd, a.simd, _MM_SHUFFLE(3, 1, 0, 2));
	b_yzx = _mm_shuffle_ps(b.simd, b.simd, _MM_SHUFFLE(3, 0, 2, 1));
	result.simd = _mm_sub_ps(
		_mm_mul_ps(a_yzx, b_zxy),
		_mm_mul_ps(a_zxy, b_yzx)
	);
	return result;
}

t_vec3	vec3_unit(t_vec3 vec)
{
	float	len;

	len = vec3_length(vec);
	return (vec3_div_vec(vec, len));
}
