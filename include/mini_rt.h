#ifndef MINI_RT_H
# define MINI_RT_H

# include "MLX42/MLX42.h"
# include "constants.h"
# include "get_next_line.h"
# include "libft.h"
# include "vec3.h"
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
typedef struct s_info		t_info;

// Represents a color.
typedef t_vec3				t_color;

// Represents a point.
typedef t_vec3				t_point;

// Represents the type of ray.
typedef enum e_ray_type
{
	NULL_RAY,
	CAM_RAY,
	SHADOW_RAY,
	REFECTION_RAY,
}							t_ray_type;

// Represents a ray.
//
// orig: the start point of a ray.
// direc: the direction vector of a ray.
// type: the type of a ray.
typedef struct s_ray
{
	t_vec3					orig;
	t_vec3					direc;
	t_ray_type				type;
}							t_ray;

// Represents the type of materials.
typedef enum e_type
{
	GLASS = 20,
	METAL,
	DIFFUSE,
	LIGHT,
}							t_type;

// Represents a material.
//
// albedo: the color of material.
// albedo2: the color of material, applied for checker boarder only.
// scale: the width of checker border texture.
// texture_img_idx: the idx of texture images.
// type_material: the type of materail.
// scatter: the function to scatter.
//
// texture_get_color: the function pointer to get the color of texture.
//  - material: the pointer to itself.
//  - rec: the hit record for u, v which are the surface coordinates.
//  - returns: the color of the point.
typedef struct s_material
{
	t_vec3					albedo;
	t_vec3					albedo2;
	int						texture_img_idx;
	float					scale;
	float					fuzz;
	float					ref_idx;
	t_type					type_material;

	bool					(*scatter)(t_ray *r_in, t_hit_record *rec,
							t_vec3 *attenuation, t_ray *scattered);
	t_color					(*texture_get_color)(t_info *info, t_material *mat,
							t_hit_record *rec);
}							t_material;

// Represents a memory block on heap.
typedef struct s_arena
{
	char					*arena_start;
	char					*current;
	size_t					total_size;
	size_t					used_size;
}							t_arena;

// Represents a camera.
//
// Some basic definations:
//
// 1 observation point: the observation window of a traditional camera.
// 2 image plane: the lcd screen in viewfinder (not the camera body).
//              (a easier way to understand it)
// 3 direction: the point of a ray where the distance is 1.
// 4 world space coordinator system: we use "right hand rule":
// - the left-bottom corner of the image plane is at 0, 0, 0.
// - the right-top corner of the image plane is at 200, 100, 0.
//   if the width of image is 200, and the height is 100.
// - the object ahead is at a place like 30, 10, -10,
//   when a object is at 30, 10, 10, it's behind the camera so that we
//   cannnot see it.
//
//
// These 5 properties need to be passed when init a camera.
//
// 1 image_width: the width of the viewpoint in pixel.
// 2 image_height: the height of the viewpoint in pixel.
// 3 point: the oberservation point of the camera.
// 4 orient: the direction vector from oberservation point to the image plane.
// 5 hov: the Horizontal Field of View, means the width of the view point.
//
//
// These are helper properties, and the value is assigned when init the camera.
//
// look_at: the center point of the image plane.
//
// vfov: the Vertical Field of View, means the angle of viewpoint,
//       the value is affected by focal which is the distance
//       from point of camera to point of image, and the size of image.
//       vfov = 2 * arctan((sizeof_image_plane / 2) / distance)
//
// vup: The up direction in world space (Y-axis direction).
//      It normally points to (0, 1, 0),
//    	representing the world's upward direction.
//
// u: the rightward unit vector in the image plane, the direction to right.
//    when the camara is normally placed, the u is 1, 0, 0.
//    = unit(cross(vup, w)).
// v: the upward unit vector in the image plane, the direction to up.
//    when the camara is normally placed, the u is 0, 1, 0.
//    = unit(cross(w, u));
// w: the forward unit vector from the observation point towards the image plane
//    the direction to front. (-orient)
//
// aspect_ratio: the aspect ratio of image plane.
//
// focal_length: the distance from the camera's observation point to the image plane.
//
// top_left: the top-left pixel of the image plane.
// pixel00_loc: the center of top-left pixel.
// a pixel is an area, not a point. so pixel00_loc is the center of top_left.
//
// pixel_delta_u: the horizontal vector step between adjacent pixel centers.
// pixel_delta_v: the vertical vector step between adjacent pixel centers.
// the world-space distance between 2 image plane pixels.
//
// viewport_height: the height of image plane in world space coordinator.
// viewport_width: the width of the image plane world space coordinator.
//
// viewpoint_u: a vector of the width of the image plane. u * viewport_width.
// viewpoint_v: a vector of the height of the image plane. v * viewport_height.
// combines both length and direction, as well as a line.
//
// dist: the direction from the observation point to the center of image plane.
// right: the camera's right vector, just a temp variable.
typedef struct s_cam
{
	// Set to default.
	int						image_width;
	int						image_height;

	// From Parsing.
	t_point					point;
	t_vec3					orient;
	float					hov;

	// Need to be calculated.
	t_point					look_at;
	float					vfov;
	float					aspect_ratio;
	t_point					pixel00_loc;
	t_vec3					pixel_delta_u;
	t_vec3					pixel_delta_v;
	t_vec3					u;
	t_vec3					v;
	t_vec3					w;
	t_vec3					vup;
	float					focal_length;
	float					viewport_height;
	float					viewport_width;
	t_vec3					viewport_u;
	t_vec3					viewport_v;
	t_vec3					top_left;
	t_vec3					right;

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

// Represents the hit record of an object.
//
// p: the intersection point.
// normal: the surface normal at the intersection point.
//         for sphere, it's the direction from p to the center of the sphere.
//         - For a plane, it is the constant normal direction of the plane.
//         - For a cylinder,
//           - side: The normal is perpendicular to the cylinder's axis.
//           - top/bottom: The normal is aligned with the cylinder’s axis (+/-).
// material: material of the object at the intersection point.
// t: the distance from the ray's start point to the intersection point.
// front_face: is the ray from outside, or inside the obj.
// u, v: surface coordinates.
typedef struct s_hit_record
{
	t_vec3					p;
	t_vec3					normal;
	t_material				*material;
	float					t;
	bool					front_face;
	bool					ray_type;
	float					u;
	float					v;
}							t_hit_record;

// Represents a distance interval.
typedef struct s_interval
{
	float					min;
	float					max;
}							t_interval;

// Represents an object.
//
// point: the center point, applies for a sphere.
// radius: the radius of an object, applies for a sphere.
// height: the height of an object, applies for a cylinder.
// br_ratio: the bright ratio, applies for a light.
// rgb: the color of an object.
// normal: the normal of an object.
// type_material: the type of materail.
// material: the materail of an object.
//
// hit: the function pointer to the hit function.
//  - obj: the pointer to itself.
//  - ray: the ray to the object.
//  - interval: the distance range of the ray.
//  - rec: the hit record, will be assigned.
//  - return if hit.
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

// Reprects the state of the program.
//
// arena: a memeory block.
// mlx: the pointer to render engine.
// img: the pointer to the image of render engine.
// textures: the textures.
// c: the camera.
// a: the ambient light.
// obj: the objects.
// lights: the lights.
// pl_count: the count of planes.
// sp_count: the count of spheres.
// cy_count: the count of cylinders.
// light_count: the count of lights.
// obj_count: the count of all the objects.
// texture_count: the count of textures.
typedef struct s_info
{
	t_arena					*arena;
	mlx_t					*mlx;
	mlx_image_t				*img;
	t_cam					c;
	t_alight				a;
	mlx_texture_t			**textures;
	t_obj					*obj;
	t_obj					**lights;
	int						index;
	unsigned int			pl_count;
	unsigned int			sp_count;
	unsigned int			cy_count;
	unsigned int			light_count;
	unsigned int			obj_count;
	unsigned int			texture_count;
	bool					hit_itself;
	bool					light_outside;
	bool					camera_outside;
}							t_info;

/*   Functions for parser.    */

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
void						create_light_info(t_info *info, char **split, int i,
								bool *isvalid);
void						create_object_info(t_info *info, char **split);
void						assign_typematerial_info(t_info *info,
								char *material, int i, char **split);
void						free_all(t_info *info);
void						free_arena_exit(t_info *info);
void						exit_free_parser(t_info *info, char **split, int n);

/* HIT OBJ*/
// Check the `hit` in t_obj.

// @brief Returns if there is an object is hit by the ray,
// and the distance is in the interval.
//
// @param info: the pointer to state of the program.
// @param ray: the ray to hit.
// @param [rec]: the value is assigned by the function.
// @param interval: the required inteval.
bool						world_hit(t_info *info, t_ray *ray,
								t_hit_record *rec, t_interval *interval);

// @brief Returns if there is an object is hit by the shadow ray,
// and the distance is in the interval.
//
// @param info: the pointer to state of the program.
// @param ray: the ray to hit.
// @param [rec]: the value is assigned by the function.
// @param interval: the required inteval.
bool						world_hit_shadow(t_info *info, t_ray *ray,
								t_hit_record *rec, t_interval *interval);

bool						sp_hit(t_obj *sphere, t_ray *ray,
								t_interval *interval, t_hit_record *rec);
bool						pl_hit(t_obj *plane, t_ray *ray,
								t_interval *interval, t_hit_record *rec);
bool						cy_hit(t_obj *cy, t_ray *ray, t_interval *interval,
								t_hit_record *rec);
bool						cn_hit(t_obj *cone, t_ray *ray, t_interval *interval, 
								t_hit_record *rec);

/* Camera */

// @brief starts the camera, render the image to screen.
//
// @param info: pointer to the state of the program.
void						camera_start(t_info *info);

// @brief resizes the camera, re-render the image to screen.
//
// @param info: pointer to the state of the program.
// @param image_width, image_height: the new size of the image.
void						camera_resize_screen(t_info *info, int image_width,
								int image_height);

// @brief to render the screen.
//
// It inits the camera by the assigned properties in parsing.
// Then iterates all pixels to render the screen.
//
// @param info: pointer to the state of the program.
void						camera_render(t_info *info);

/*        Vector Math Functions                     */

// @brief return (-1 * vec);
t_vec3						vec3_flip_minus(t_vec3 vec);

// @brief when we sqrt the result, we will get the length.
float						vec3_length_squared(t_vec3 vec);

// @brief return the length of a vec which is the result of a subtraction.
//        = sqrt(length_squared)
float						vec3_length(t_vec3 vec);

// @brief returns a new vector that is perpendicular to both A and B.
// - Point your right-hand fingers in the direction of A.
// - Curl your fingers towards B.
// - Your thumb points in the direction of A × B.
t_vec3						vec3_cross(t_vec3 vec1, t_vec3 vec2);

// @brief the angle of 2 vecs.
//        = 0 when angle is 90°, > 0 when 0 - 90°, < 0 when 90 - 180°.
float						vec3_dot(t_vec3 vec1, t_vec3 vec2);

// @brief returns the value at the point where the distance is 1 on a ray.
t_vec3						vec3_unit(t_vec3 vec);

t_vec3						vec3_new(float x, float y, float z);
void						vec3_print(t_vec3 vec);
void						vec3_normalize(t_vec3 *vec);
t_vec3						vec3_add_vecs(t_vec3 vec1, t_vec3 vec2);
t_vec3						vec3_sub_vecs(t_vec3 vec1, t_vec3 vec2);
t_vec3						vec3_mul_vecs(t_vec3 vec1, t_vec3 vec2);
t_vec3						vec3_mul_vec(t_vec3 vec, float scalar);
t_vec3						vec3_div_vec(t_vec3 vec1, float scalar);
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
t_color						vec3_mul_colors(t_vec3 vec1, t_vec3 vec2);
t_color						vec3_sky(void);
bool						vec3_near_black(t_color color);
t_color						vec3_black(void);
t_color						vec3_avoid_overflow(t_vec3 color);

/*			INTERVAL						*/

// @brief 0.001 to INF
t_interval					interval_default(void);

// @brief -INF to INF
t_interval					interval_empty(void);

// @brief returns the max - min.
float						interval_size(t_interval interval);

// @brief return if the given value is in the interval.
bool						interval_surrounds(t_interval *interval,
								float value);

/*			Utils							*/

// @brief to calculate the destination point of a ray.
//
// @param ray to destination.
// @param the distance to destination.
// @return the destination point.
t_point						ray_at(t_ray *ray, double t);
void						set_face_normal(t_ray r, t_vec3 outward_normal,
								t_hit_record *rec);


// @brief To solve if and what is the valid `t` in : at² + bt + c = 0
//
// The question equlas:
//     t = (-b ± sqrt(b² - 4ac)) / (2a)
//
// @param a b c: a, b, c in at² + bt + c = 0.
// @param [t] to store the possible result `t`, and t[0] < t[1].
// @return if there is at least one valid `t`.
bool						cal_quadratic(float a, float b, float c, float t[2]);			


bool						lambertian_scatter(t_ray *r_in, t_hit_record *rec,
								t_vec3 *attenuation, t_ray *scattered);
bool						metal_scatter(t_ray *r_in, t_hit_record *rec,
								t_vec3 *attenuation, t_ray *scattered);
bool						dielectric_scatter(t_ray *r_in, t_hit_record *rec,
								t_vec3 *attenuation, t_ray *scattered);
bool						light_scatter(t_ray *r_in, t_hit_record *rec,
								t_vec3 *attenuation, t_ray *scattered);

/* UI, the hooks to handle the UI event */

void						handle_win_close_event(void *param);
void						handle_key_press_event(mlx_key_data_t keydata,
								void *param);
void						handle_screen_resize(int32_t width, int32_t height,
								void *param);

/* Texture */

t_color						texutre_constant_color(t_info *info,
								t_material *mat, t_hit_record *rec);
t_color						texture_checker_color(t_info *info, t_material *mat,
								t_hit_record *rec);
t_color						texture_img_color(t_info *info, t_material *mat,
								t_hit_record *rec);

#endif