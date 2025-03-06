#pragma once
#include "common.h"

typedef struct
{
	uint8_t *buf;
	size_t buf_len;
	size_t prev_offset;
	size_t curr_offset;
} Arena;

typedef struct
{
	Arena *arena;
	size_t prev_offset;
	size_t curr_offset;
} TempArena;

void *arena_alloc(Arena *a, size_t size);
void *arena_alloc_align(Arena *a, size_t size, size_t align);
void arena_init(Arena *a, void *backing_buffer, size_t buffer_len);
void arena_free(Arena *a);
void *arena_resize_align(Arena *a, void *old_memory, size_t old_size, size_t new_size, size_t align);
void *arena_resize(Arena *a, void *old_memory, size_t old_size, size_t new_size);

TempArena temp_arena_init(Arena *arena);
void temp_arena_end(TempArena temp);
