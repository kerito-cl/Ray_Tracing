# include "vec3.bonus.h"
# include "constants.h"
# include <stdbool.h>

inline t_vec3 vec3_new(float x, float y, float z) {
    t_vec3 result;

    result.simd = _mm_set_ps(0.0f, z, y, x);
    return result;
}

inline t_vec3 vec3_add_vecs(t_vec3 a, t_vec3 b) {
    t_vec3 result;

    result.simd = _mm_add_ps(a.simd, b.simd);
    return result;
}

inline t_vec3 vec3_sub_vecs(t_vec3 a, t_vec3 b) {
    t_vec3 result;

    result.simd = _mm_sub_ps(a.simd, b.simd);
    return result;
}

inline t_vec3 vec3_mul_vecs(t_vec3 a, t_vec3 b) {
    t_vec3 result;

    result.simd = _mm_mul_ps(a.simd, b.simd);
    return result;
}

inline t_vec3 vec3_mul_vec(t_vec3 vec, float scalar) {
    t_vec3 result;

    result.simd = _mm_mul_ps(vec.simd, _mm_set1_ps(scalar));
    return result;
}

inline t_vec3 vec3_div_vec(t_vec3 vec, float scalar) {
    t_vec3 result;

    result.simd = _mm_div_ps(vec.simd, _mm_set1_ps(scalar));
    return result;
}

inline float vec3_dot(t_vec3 a, t_vec3 b) {
	float f[4];
    
    _mm_storeu_ps(f, _mm_mul_ps(a.simd, b.simd));
    return f[0] + f[1] + f[2];
}

inline float vec3_length_squared(t_vec3 vec) {
	float f[4];
    
    _mm_storeu_ps(f, _mm_mul_ps(vec.simd, vec.simd));
    return f[0] + f[1] + f[2];
}

inline void vec3_print(t_vec3 vec) {
    float f[4];

    _mm_storeu_ps(f, vec.simd);
    printf("x: %f, y: %f, z: %f\n", f[0], f[1], f[2]);
}

inline bool vec3_near_zero(t_vec3 vec) {
    float f[4];

    _mm_storeu_ps(f, vec.simd);
    return fabsf(f[0]) < S &&
           fabsf(f[1]) < S &&
           fabsf(f[2]) < S;
}

inline t_vec3 vec3_cross(t_vec3 a, t_vec3 b) {
    t_vec3 result;

    result.simd = _mm_sub_ps(_mm_mul_ps(_mm_shuffle_ps(a.simd, a.simd, _MM_SHUFFLE(3, 0, 2, 1)), _mm_shuffle_ps(b.simd, b.simd, _MM_SHUFFLE(3, 1, 0, 2))), _mm_mul_ps(_mm_shuffle_ps(a.simd, a.simd, _MM_SHUFFLE(3, 1, 0, 2)), _mm_shuffle_ps(b.simd, b.simd, _MM_SHUFFLE(3, 0, 2, 1))));
    return result;
}

inline t_vec3 vec3_min(t_vec3 a, t_vec3 b) {
    t_vec3 result;

    result.simd = _mm_min_ps(a.simd, b.simd);
    return result;
}

inline t_vec3 vec3_max(t_vec3 a, t_vec3 b) {
    t_vec3 result;

    result.simd = _mm_max_ps(a.simd, b.simd);
    return result;
}