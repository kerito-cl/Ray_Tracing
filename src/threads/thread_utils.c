/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:40:47 by mquero            #+#    #+#             */
/*   Updated: 2025/04/09 09:45:41 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/// @details
/// The `render` function is the core per-thread rendering routine. It renders
/// pixels from a specific row and column 
/// pattern based on the thread's start_row.
/// Threads render every Nth column (N = THREADS_AMOUNT),
/// allowing parallel column -
///	wise rendering.
/// The function checks for an abort signal or stop condition on 
/// each pixel loop.
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

/// @details
/// This is the main loop for each thread. 
///It synchronizes the thread pool using atomic
/// counters and waits for work (i.e., a frame render) to become available.
/// Threads are reused across frames and sleep when idle.
///
/// Uses `start_task` to coordinate readiness,
/// and `work_available` as a trigger for new work.
/// A change in `work_available` indicates a new frame should be rendered.
/// The `render` function is called to handle pixel drawing.
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

// @brief
/// Initializes the thread pool by preparing per-thread 
/// data and spawning all threads.
/// Each thread is assigned a `start_row` to determine 
/// which columns it will render.
/// Threads are created once and reused for future render calls.
/// Atomic variables are initialized to manage 
/// synchronization between render calls.
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
/// @details
/// This function ensures that all threads are ready 
/// before beginning a render task.
/// It waits until each thread increments the `start_task` counter,
/// signaling readiness.
/// Also used to cleanly synchronize the start 
/// of a frame render from the main thread.

void	wait_for_threads(t_info *info)
{
	atomic_store(&info->pool.abort_signal, 0);
	while (atomic_load(&info->pool.start_task) != (THREADS_AMOUNT))
		usleep(200);
}
