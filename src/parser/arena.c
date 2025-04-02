
#include "mini_rt.h"

t_arena	*arena_init(size_t size)
{
	t_arena	*arena;

	arena = malloc(sizeof(t_arena));
	if (!arena)
		return (NULL);
	arena->arena_start = ft_calloc(1, size);
	if (!arena->arena_start)
	{
		free(arena);
		return (NULL);
	}
	arena->current = arena->arena_start;
	arena->total_size = size;
	arena->used_size = 0;
	return (arena);
}

void	*arena_alloc(t_arena *arena, size_t size)
{
	void	*ptr;

	ptr = arena->current;
	arena->current += size;
	arena->used_size += size;
	return (ptr);
}

void	arena_reset(t_arena *arena)
{
	arena->current = arena->arena_start;
	arena->used_size = 0;
}

void	arena_free(t_arena *arena)
{
	free(arena->arena_start);
	free(arena);
}
