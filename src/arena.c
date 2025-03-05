
#include "mini_rt.h"

t_arena *arena_init(size_t size)
{
    t_arena *arena;

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

bool arena_expand(t_arena *arena, size_t new_size)
{
    size_t used_offset;
    char *new_block;

    used_offset = arena->current - arena->arena_start;
    new_block = ft_realloc(arena->arena_start, new_size);
    if (!new_block)
        return (false);
    arena->arena_start = new_block;
    arena->current = new_block + used_offset;
    arena->total_size = new_size;
    return (true);
}

void *arena_alloc(t_arena *arena, size_t size)
{
    void *ptr;

    if (arena->used_size + size > arena->total_size)
    {
        if (!arena_expand(arena, arena->total_size * 2))
            return (NULL);
    }
    ptr = arena->current;
    arena->current += size;
    arena->used_size += size;
    return (ptr);
}

void arena_reset(t_arena *arena)
{
    arena->current = arena->arena_start;
    arena->used_size = 0;
}

void arena_free(t_arena *arena)
{
    free(arena->arena_start);
    free(arena);
}
