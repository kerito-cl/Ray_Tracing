#include "mini_rt.h"

void	assign_lights(t_info *info, char *material, int i, char **split)
{
	info->obj[i].type_material = LIGHT;
	info->obj[i].material.albedo = vec3_mul_vec(info->obj[i].rgb,
			info->obj[i].br_ratio);
	info->obj[i].material.scatter = light_scatter;
}

void	assign_metal(t_info *info, char *material, int i, char **split)
{
	info->obj[i].type_material = METAL;
	info->obj[i].br_ratio = METAL_BR_RATIO;
	info->obj[i].material.albedo = vec3_mul_vec(info->obj[i].rgb,
			info->obj[i].br_ratio);
	info->obj[i].material.fuzz = METAL_FUZZ;
	info->obj[i].material.scatter = metal_scatter;
}

void	assign_glass(t_info *info, char *material, int i, char **split)
{
	info->obj[i].type_material = GLASS;
	info->obj[i].material.albedo = info->obj[i].rgb;
	info->obj[i].material.ref_idx = GLASS_REF_IDX;
	info->obj[i].material.scatter = dielectric_scatter;
}

void	assign_air(t_info *info, char *material, int i, char **split)
{
	info->obj[i].type_material = AIR;
	info->obj[i].material.albedo = info->obj[i].rgb;
	info->obj[i].material.ref_idx = AIR_REF_IDX;
	info->obj[i].material.scatter = dielectric_scatter;
}

void	assign_water(t_info *info, char *material, int i, char **split)
{
	info->obj[i].type_material = AIR;
	info->obj[i].material.albedo = info->obj[i].rgb;
	info->obj[i].material.ref_idx = AIR_REF_IDX;
	info->obj[i].material.scatter = dielectric_scatter;
}
