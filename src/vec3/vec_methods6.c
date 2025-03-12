#include "mini_rt.h"

t_color vec3_sky(void)
{
	return vec3_new(0.01960784313f, 0.01960784313f, 1.0f);
}

t_color vec3_shadow(void)
{
    return (vec3_new(0, 0, 0));
}
