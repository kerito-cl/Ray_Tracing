#ifndef VEC3_H
# define VEC3_H

// Represents a vector.
typedef union __attribute__((aligned(16))) s_vec3 {
	struct {
		float x, y, z, w;
	};
	__m128 simd;
} t_vec3;

#endif