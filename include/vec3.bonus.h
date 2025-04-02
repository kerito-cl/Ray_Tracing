#ifndef VEC3_H
# define VEC3_H

# include <xmmintrin.h> 

typedef struct s_vec3 {
    __m128 simd;
} t_vec3;

#endif