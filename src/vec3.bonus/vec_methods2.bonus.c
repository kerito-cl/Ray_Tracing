#include "mini_rt.h"
#include <math.h>

void	vec3_print(t_vec3 vec)
{
	printf("x: %f, y: %f, z: %f\n", vec.x, vec.y, vec.z);
}

bool	vec3_near_zero(t_vec3 vec)
{
	int mask;
	__m128 abs;
	__m128 cmp;

	abs = _mm_andnot_ps(_mm_set1_ps(-0.0f), vec.simd);
	cmp = _mm_cmplt_ps(abs, _mm_set1_ps(S));
	mask = _mm_movemask_ps(cmp);
	return (mask & 0b0111) == 0b0111;
}

t_vec3	vec3_add_vecs(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3 result;

	result.simd = _mm_add_ps(vec1.simd, vec2.simd);
	return result;
}

t_vec3	vec3_sub_vecs(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3 result;

	result.simd = _mm_sub_ps(vec1.simd, vec2.simd);
	return result;
}

t_vec3	vec3_mul_vecs(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3 result;

	result.simd = _mm_mul_ps(vec1.simd, vec2.simd);
	return result;
}
