# include "vec3.bonus.h"
# include "constants.h"

inline t_vec3 vec3_unit(t_vec3 vec)
{
    return vec3_div_vec(vec, vec3_length(vec));
}

inline float vec3_length(t_vec3 vec)
{
    return sqrtf(vec3_length_squared(vec));
}

inline t_vec3 vec3_random(void)
{
    return vec3_new(RANDOM_FLOAT, RANDOM_FLOAT, RANDOM_FLOAT);
}

inline t_vec3 vec3_random_range(float min, float max)
{
    return vec3_new(
        RANDOM_FLOAT_RANGE(min, max),
        RANDOM_FLOAT_RANGE(min, max),
        RANDOM_FLOAT_RANGE(min, max)
    );
}

inline t_vec3	vec3_random_unit_vector(void)
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

inline t_vec3	vec3_random_on_hemisphere(t_vec3 normal)
{
	t_vec3	random;

	random = vec3_random_unit_vector();
	if (vec3_dot(random, normal) > 0)
		return (random);
	return (vec3_flip_minus(random));
}

inline t_vec3	vec3_reflect(t_vec3 v, t_vec3 n)
{
	t_vec3	vec;

	vec = vec3_mul_vec(n, 2 * vec3_dot(v, n));
	return (vec3_sub_vecs(v, vec));
}

inline t_vec3	vec3_refract(t_vec3 uv, t_vec3 n, float etai_over_etat)
{
	float	cos_theta;
	t_vec3	r_out_perp;
	t_vec3	r_out_parallel;

	cos_theta = fminf(vec3_dot(vec3_flip_minus(uv), n), 1.0);
	r_out_perp = vec3_mul_vec(vec3_add_vecs(uv, vec3_mul_vec(n, cos_theta)),
			etai_over_etat);
	r_out_parallel = vec3_mul_vec(n, -sqrtf(fabsf((float)1.0
					- vec3_length_squared(r_out_perp))));
	return (vec3_add_vecs(r_out_perp, r_out_parallel));
}

inline t_vec3	vec3_random_in_unit_disk(void)
{
	t_vec3	p;

	while (true)
	{
		p = vec3_new(RANDOM_FLOAT_RANGE(-1, 1), RANDOM_FLOAT_RANGE(-1, 1), 0);
		if (vec3_length_squared(p) < 1)
			return (p);
	}
}

inline t_color	vec3_mul_colors(t_vec3 vec1, t_vec3 vec2)
{
	t_color	color;

	color.x = vec1.x * vec2.x;
	if (color.x > 1)
		color.x = 1;
	color.y = vec1.y * vec2.y;
	if (color.y > 1)
		color.y = 1;
	color.z = vec1.z * vec2.z;
	if (color.z > 1)
		color.z = 1;
	return (color);
}

inline t_color	vec3_sky(void)
{
	return (vec3_new(0.13f, 0.13f, 0.13f));
}

inline bool	vec3_near_black(t_color color)
{
	return (color.x < 0.001f && color.y < 0.001f && color.z < 0.001f);
}

inline t_color	vec3_black(void)
{
	return (vec3_new(0, 0, 0));
}

inline t_color	vec3_avoid_overflow(t_vec3 color)
{
	return (vec3_new(fmaxf(color.x, 1), fmaxf(color.y, 1), fmaxf(color.z, 1)));
}