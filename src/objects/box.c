# include "mini_rt.h"
# include "vars.h"

// @brief set the normal of a box.
static void set_normal(t_obj *box, t_hit_record *rec)
{
    if (fabsf(rec->p.x - box->min.x) < S)
        rec->normal = vec3_new(-1, 0, 0);
    else if (fabsf(rec->p.x - box->max.x) < S)
        rec->normal = vec3_new(1, 0, 0);
    else if (fabsf(rec->p.y - box->min.y) < S)
        rec->normal = vec3_new(0, -1, 0);
    else if (fabsf(rec->p.y - box->max.y) < S)
        rec->normal = vec3_new(0, 1, 0);
    else if (fabsf(rec->p.z - box->min.z) < S)
        rec->normal = vec3_new(0, 0, -1);
    else
        rec->normal = vec3_new(0, 0, 1);
}

// @brief set the uv of a box.
static void set_uv(t_obj *box, t_hit_record *rec)
{
    t_vec3 local;
	t_vec3 size;
     
    local = vec3_sub_vecs(rec->p, box->min);
    size = vec3_sub_vecs(box->max, box->min);
	if (fabsf(rec->normal.x) > 0.9f) {
		rec->u = local.z / size.z;
		rec->v = local.y / size.y;
	} else if (fabsf(rec->normal.y) > 0.9f) {
		rec->u = local.x / size.x;
		rec->v = local.z / size.z;
	} else {
		rec->u = local.x / size.x;
		rec->v = local.y / size.y;
	}
	rec->u = fmodf(rec->u, 1.0f);
	rec->v = fmodf(rec->v, 1.0f);
	if (rec->u < 0) rec->u += 1.0f;
	if (rec->v < 0) rec->v += 1.0f;
}

// @details returns if the given aabb box is hit by the given ray in given interval.
// and fill the given rec.
//
//
// The math is based on the idea of "slab method":
// - We create slabs for the box first.
// - For each axis (x, y, z), we compute the intersection of the ray with the two slabs
//   (planes) that define the min and max bounds along that axis.
// - We keep track of the largest minimum t (entry point) and the smallest maximum t (exit point).
// - If at any point, t_min > t_max, the ray misses the box.
//
// The process:
// 1. Compute the inverse direction of the ray to avoid division in the loop.
// 2. Calculate intersection t-values with all 3 slabs.
// 3. Find the overlapping t interval.
// 4. If there's no overlap, return false.
// 5. Calculate the hit point, face normal, and uv for texture.
bool	box_hit(t_obj *box, t_ray *ray, t_interval *interval, t_hit_record *rec)
{
    t_hit_box_vars var;

    var.inv_d = vec3_div(1.0f, ray->direc);
	float	tmin = interval->min;
	float	tmax = interval->max;
	var.t0 = vec3_mul_vec(vec3_sub_vecs(box->min, ray->orig), var.inv_d);
	var.t1 = vec3_mul_vec(vec3_sub_vecs(box->max, ray->orig), var.inv_d);
	var.tmin = vec3_min(var.t0, var.t1);
	var.tmax = vec3_max(var.t0, var.t1);
	var.tminf = fmaxf(fmaxf(var.tmin.x, var.tmin.y), fmaxf(interval->min, var.tmin.z));
	var.tmaxf = fminf(fminf(var.tmax.x, var.tmax.y), fminf(interval->max, var.tmax.z));
	if (var.tmaxf < var.tminf)
		return false;
	rec->t = var.tminf;
	rec->p = ray_at(ray, var.tminf);
	rec->material = &box->material;
    set_normal(box, rec);
    set_face_normal(ray, rec->normal, rec);
    set_uv(box, rec);
	return true;
}
