#ifndef MINI_RT_H
# define MINI_RT_H
# define MAX_WIDTH 1920
# define MAX_HEIGHT 1080
# define INFINITY 1080

# include "MLX42/MLX42.h"
# include "constants.h"
# include "get_next_line.h"
# include "libft.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_material	t_material;
typedef struct s_hit_record	t_hit_record;
typedef struct s_obj		t_obj;

typedef struct s_vec3
{
	float					x;
	float					y;
	float					z;
}							t_vec3;

typedef t_vec3				t_color;
typedef t_vec3				t_point;

typedef struct s_ray
{
	t_vec3					orig;
	t_vec3					direc;
}							t_ray;

typedef enum e_type
{
	GLASS = 20,
	METAL,
	DIFFUSE,
	LIGHT,
}							t_type;

typedef struct s_material
{
	t_vec3					albedo;
	float					fuzz;
	float					ref_idx;
	t_type					type_material;

	bool					(*scatter)(t_ray *r_in, t_hit_record *rec,
							t_vec3 *attenuation, t_ray *scattered);
}							t_material;

typedef struct s_arena
{
	char					*arena_start;
	char					*current;
	size_t					total_size;
	size_t					used_size;
}							t_arena;

typedef struct s_cam
{
	// Set to default.
	int						image_width;
	int						image_height;

	// From Parsing.
	t_point					point;
	t_vec3					orient;
	float					fov;

	// Constant.
	t_point					look_at;

	// Need to be calculated.
	float					aspect_ratio;
	t_point					pixel00_loc;
	t_vec3					pixel_delta_u;
	t_vec3					pixel_delta_v;
	t_vec3					u;
	t_vec3					v;
	t_vec3					w;
	t_vec3					dist;
	float					focal_length;
	float					viewport_height;
	float					viewport_width;
	t_vec3					viewpoint_u;
	t_vec3					viewpoint_v;
	t_vec3					top_left;
	
}							t_cam;

typedef struct s_alight
{
	t_vec3					rgb;
	float					ratio;
}							t_alight;

typedef struct s_light
{
	t_vec3					point;
	t_vec3					rgb;
	float					br_ratio;
}							t_light;

typedef struct s_hit_record
{
	t_vec3					p;
	t_vec3					normal;
	t_material				*material;
	float					t;
	bool					front_face;
}							t_hit_record;

typedef struct s_interval
{
	float					min;
	float					max;
}							t_interval;

typedef struct s_obj
{
	t_vec3					point;
	t_vec3					rgb;
	t_vec3					normal;
	float					radius;
	float					height;
	float					br_ratio;
	bool					(*hit)(t_obj *obj, t_ray *ray, t_interval *interval,
							t_hit_record *rec);
	t_type					type_material;
	t_material				material;
}							t_obj;

typedef struct s_info
{
	t_arena					*arena;
	mlx_t					*mlx;
	mlx_image_t				*img;
	t_cam					c;
	t_alight				a;
	t_light					l;
	t_obj					*obj;
	unsigned int			pl_count;
	unsigned int			sp_count;
	unsigned int			cy_count;
	unsigned int			light_count;
	unsigned int			obj_count;
}							t_info;

void						print_vec3(t_vec3 vec3);

t_arena						*arena_init(size_t size);
void						arena_free(t_arena *arena);
void						*arena_alloc(t_arena *arena, size_t size);
void						throw_error(int flag);
int							check_if_rt(char *str);
void						parse(char *file, t_info *info);
void						freesplit(char **strs);
void						new_vec3_for_parsing(t_vec3 *vec3, char **cvec,
								bool *isvalid, bool if_rgb);
void						create_object_info(t_info *info, char **split);
void						free_all(t_info *info);
void						free_arena_exit(t_info *info);
void						exit_free_parser(t_info *info, char **split, int n);

/* HIT OBJ*/
bool						world_hit(t_info *info, t_ray *ray,
								t_hit_record *rec, t_interval *interval);
bool						sp_hit(t_obj *sphere, t_ray *ray,
								t_interval *interval, t_hit_record *rec);
bool						pl_hit(t_obj *plane, t_ray *ray,
								t_interval *interval, t_hit_record *rec);
bool						cy_hit(t_obj *cy, t_ray *ray, t_interval *interval,
								t_hit_record *rec);

/* Camera */

void 						camera_resize_screen(t_info *info, int image_width, int image_height);
void 						camera_move(t_info *info, t_point point, float fov, t_vec3 orient);
void 						camera_render(t_info *info);
void 						camera_start(t_info *info, t_point point, float fov, t_vec3 orient);
t_ray camera_get_ray(t_cam *c, int i, int j);
t_color camera_ray_color(t_info *info, t_ray ray, t_obj **world, int depth);


/*        OPERATIONS                       */

t_vec3						vec3_new(float x, float y, float z);
void						vec3_print(t_vec3 vec);
void						vec3_normalize(t_vec3 *vec);
t_vec3						vec3_flip_minus(t_vec3 vec);
float						vec3_length_squared(t_vec3 vec);
float						vec3_length(t_vec3 vec);
t_vec3						vec3_add_vecs(t_vec3 vec1, t_vec3 vec2);
t_vec3						vec3_sub_vecs(t_vec3 vec1, t_vec3 vec2);
t_vec3						vec3_mul_vecs(t_vec3 vec1, t_vec3 vec2);
t_vec3						vec3_mul_vec(t_vec3 vec, float scalar);
t_vec3						vec3_div_vec(t_vec3 vec1, float scalar);
t_vec3						vec3_cross(t_vec3 vec1, t_vec3 vec2);
float						vec3_dot(t_vec3 vec1, t_vec3 vec2);
t_vec3						vec3_unit(t_vec3 vec);
t_vec3						vec3_random(void);
t_vec3						vec3_random_range(float min, float max);
t_vec3						vec3_random_unit_vector(void);
t_vec3						vec3_random_on_hemisphere(t_vec3 normal);
bool						vec3_near_zero(t_vec3 vec);
t_vec3						vec3_reflect(t_vec3 v, t_vec3 n);
t_vec3						vec3_refract(t_vec3 uv, t_vec3 n,
								float etai_over_etat);
t_vec3						vec3_copy(t_vec3 vec);
t_vec3						vec3_random_in_unit_disk(void);

/*			INTERVAL						*/

t_interval					interval_default(void);
t_interval					interval_empty(void);
t_interval					interval_universe(void);
float						interval_size(t_interval interval);
bool						interval_contains(t_interval interval, float value);
bool						interval_surrounds(t_interval *interval,
								float value);
float						interval_clamp(t_interval interval, float value);

/*			COLOR						*/

t_color 					get_shadow_light(t_info *info);
t_color 					get_light_color(t_info *info, t_ray *shadow_ray, t_ray *cam_ray);
t_color    					get_ambient_light(t_info *info);

/*			Utils							*/

t_point						ray_at(t_ray *ray, double t);
void						set_face_normal(t_ray r, t_vec3 outward_normal,
								t_hit_record *rec);
bool						lambertian_scatter(t_ray *r_in, t_hit_record *rec,
								t_vec3 *attenuation, t_ray *scattered);
bool						metal_scatter(t_ray *r_in, t_hit_record *rec,
								t_vec3 *attenuation, t_ray *scattered);
bool						dielectric_scatter(t_ray *r_in, t_hit_record *rec,
								t_vec3 *attenuation, t_ray *scattered);

#endif