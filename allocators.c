#include "allocators.h"

bool is_power_of_two(uintptr_t ptr)
{
	return (ptr & (ptr - 1)) == 0;
}

uintptr_t align_foward(uint64_t ptr, size_t align)
{
	uintptr_t p, a, modulo;
	assert(is_power_of_two(align));

	p = ptr;
	a = (uintptr_t)align;
	modulo = p % (a - 1);

	if (modulo != 0)
	{
		p += a - modulo;
	}

	return p;
}

void *arena_alloc_align(Arena *a, size_t size, size_t align)
{
	uintptr_t curr_ptr = (uint64_t)a->buf + (uintptr_t)a->curr_offset;
	uintptr_t offset = align_foward(curr_ptr, align);
	offset -= (uintptr_t)a->buf;

	if (offset + size <= a->buf_len)
	{
		void *ptr = &a->buf[offset];
		a->prev_offset = offset;
		a->curr_offset = offset + size;

		memset(ptr, 0, size);
		return ptr;
	}

	return NULL;
}

#ifndef DEFAULT_ARENA_ALIGMENT
#define DEFAULT_ARENA_ALIGMENT (2 * sizeof(void *))
#endif /* ifndef MACRO */

void *arena_alloc(Arena *a, size_t size)
{
	return arena_alloc_align(a, size, DEFAULT_ARENA_ALIGMENT);
}

void arena_init(Arena *a, void *backing_buffer, size_t buffer_len)
{
	a->buf = (uint8_t *)backing_buffer;
	a->buf_len = buffer_len;
	a->prev_offset = 0;
	a->curr_offset = 0;
}

void arena_free(Arena *a)
{
	a->curr_offset = 0;
	a->prev_offset = 0;
}

void *arena_resize_align(Arena *a, void *old_memory, size_t old_size, size_t new_size, size_t align)
{
	uint8_t *old_mem = (uint8_t *)old_memory;

	assert(is_power_of_two(align));

	if (old_mem == NULL || old_size == 0)
	{
		return arena_alloc_align(a, new_size, align);
	}
	else if (a->buf <= old_mem && old_mem < a->buf + a->buf_len)
	{
		if (a->buf + a->prev_offset == old_mem)
		{
			a->curr_offset = a->prev_offset + new_size;
			if (new_size > old_size)
			{
				memset(&a->buf[a->curr_offset], 0, new_size - old_size);
			}
		}
		return old_memory;
	}
	else
	{
		assert(0 && "Memory out of bounds of the buffer in this arena");
		return NULL;
	}
}

void *arena_resize(Arena *a, void *old_memory, size_t old_size, size_t new_size)
{
	return arena_resize_align(a, old_memory, old_size, new_size, DEFAULT_ARENA_ALIGMENT);
}

TempArena temp_arena_init(Arena *arena)
{
	TempArena t_arena;
	t_arena.arena = arena;
	t_arena.prev_offset = arena->prev_offset;
	t_arena.curr_offset = arena->curr_offset;

	return t_arena;
}

void temp_arena_end(TempArena temp)
{
	temp.arena->prev_offset = temp.prev_offset;
	temp.arena->curr_offset = temp.curr_offset;
}
