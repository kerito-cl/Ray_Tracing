#include "mini_rt.h"

static bool	render(t_thrdata *thr, t_info *info, int row)
{
	int	col;

	while (row < thr->thr_info->c.image_height)
	{
		col = thr->start_row;
		while (col < thr->thr_info->c.image_width)
		{
			if (atomic_load(&info->pool.work_available) == -1)
				return (false);
			else if (atomic_load(&info->pool.abort_signal) == 0)
			{
				row = thr->thr_info->c.image_height;
				col = thr->start_row;
				return (true);
			}
			thr->ray = camera_get_ray(&info->c, col, row);
			thr->color = camera_ray_color(thr->thr_info, thr->ray,
					&thr->thr_info->obj, MAX_DEPTH);
			thr->packed_color = get_color(thr->color);
			mlx_put_pixel(info->img, col, row, thr->packed_color);
			col += THREADS_AMOUNT;
		}
		row++;
	}
	return (true);
}

static void	*thr_draw(void *param)
{
	t_thrdata	*thr;
	int			row;
	int			col;
	int			last_frame;
	t_info		*info;

	thr = (t_thrdata *)param;
	last_frame = 0;
	info = thr->thr_info;
	while (1)
	{
		if (atomic_load(&info->pool.start_task) != THREADS_AMOUNT)
			atomic_fetch_add(&info->pool.start_task, 1);
		while (atomic_load(&info->pool.work_available) == last_frame)
			usleep(2);
		atomic_fetch_add(&info->pool.start_task, -1);
		last_frame = atomic_load(&info->pool.work_available);
		row = 0;
		if (!render(thr, info, row))
		{
        	atomic_fetch_add(&info->pool.start_task, 1);
			return (NULL);
		}
	}
	return (NULL);
}

void	init_thread_pool(t_info *info)
{
	int	i;
	int	gap;

	i = 0;
	info->pool.work_available = 0;
	info->pool.start_task = 0;
	while (i < THREADS_AMOUNT)
	{
		info->pool.thr_data[i].thr_info = info;
		info->pool.thr_data[i].start_row = i;
		i++;
	}
	i = 0;
	while (i < THREADS_AMOUNT)
	{
		if (pthread_create(&info->pool.threads[i], NULL, thr_draw,
			&info->pool.thr_data[i]))
			free_all(info);
		i++;
	}
}
