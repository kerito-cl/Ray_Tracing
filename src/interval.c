#include "mini_rt.h"

t_interval	interval_empty(void)
{
	t_interval	interval;

	interval.max = INFINITY;
	interval.min = -INFINITY;
	return (interval);
}

t_interval	interval_default(void)
{
	t_interval	interval;

	interval.min = 0.001;
	interval.max = INFINITY;
	return (interval);
}

float	interval_size(t_interval interval)
{
	return (interval.max - interval.min);
}

bool	interval_surrounds(t_interval *interval, float value)
{
	return (value > interval->min && value < interval->max);
}
