#ifndef MINI_RT_H
# define MINI_RT_H
# define WIDTH 1920
# define HEIGHT 1080
# define INFINITY 1080

# include "MLX42/MLX42.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "libft.h"
# include "get_next_line.h"

typedef struct s_material t_material;
typedef struct s_hit_record t_hit_record;

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}       t_vec3;

typedef struct s_ray
{
	t_vec3 orig;
	t_vec3 direc;
}       t_ray;

typedef enum e_type
{
	GLASS = 20,
	METAL,
	DIFFUSE,
}	t_type;


typedef struct s_material
{
    t_vec3 albedo;
    float fuzz;
    float ref_idx;

    bool (*scatter)(t_material *mat, t_ray *r_in, t_hit_record *rec, t_vec3 *attenuation, t_ray **scattered);
} t_material;

typedef struct s_arena
{
    char *arena_start;
    char *current;
    size_t total_size;
    size_t used_size;
} t_arena;

typedef struct s_cam
{
	t_vec3 point;
	t_vec3 orient;
	unsigned int	fov;
}       t_cam;

typedef struct s_alight
{
	t_vec3 rgb;
	float	ratio;
}       t_alight;

typedef struct s_light
{
	t_vec3 point;
	t_vec3 rgb;
	float	br_ratio;
}       t_light;

typedef struct s_hit_record
{
    t_vec3 p;
    t_vec3 normal;
    t_material *material;
    float t;
    bool front_face;
} t_hit_record;

typedef struct s_obj
{
    t_vec3 point;
	t_vec3 rgb;
    float radius;
	t_vec3 norm;
    float height;
    bool (*hit)(t_ray *r, t_hit_record *rec);
	t_type type_material;
	t_material material;
} t_obj;

typedef struct s_info
{
	t_arena *arena;
	mlx_t *mlx;
	mlx_image_t		*img;
	t_cam c;
	t_alight a;
	t_light	l;
	t_obj *obj;
	unsigned int pl_count;
	unsigned int sp_count;
	unsigned int cy_count;
	unsigned int obj_count;
}       t_info;


void	print_vec3(t_vec3 vec3);


t_arena *arena_init(size_t size);
void arena_free(t_arena *arena);
void *arena_alloc(t_arena *arena, size_t size);
void	throw_error(int flag);
int     check_if_rt(char *str);
void    parse(char *file, t_info *info);
void	freesplit(char **strs);
void    new_vec3(t_vec3 *vec3, char **cvec, bool if_rgb);
void create_object_info(t_info *info, char **split);
void	free_all(t_info *info);
void	free_arena_exit(t_info *info);

/* HIT OBJ*/

bool sp_hit(t_ray *r, t_hit_record *rec);
bool pl_hit(t_ray *r, t_hit_record *rec);
bool cy_hit(t_ray *r, t_hit_record *rec);


/*        OPERATIONS                       */

float    dot_calculation(t_vec3 vec1, t_vec3 vec2);
float    vec_length(t_vec3 vec1);
void    vec_normalize(t_vec3 *vec1);
void    vec_substract(t_vec3 *vec1, t_vec3 vec2);
void    vec_add(t_vec3 *vec1, t_vec3 vec2);
void    get_point_from_ray(t_vec3 *point ,t_ray ray, float t);
t_vec3    multiply_colors(t_vec3 startcolor , t_vec3 endcolor);
void    multiply_vec_by_num(t_vec3 *vec3, float mult);


#endif