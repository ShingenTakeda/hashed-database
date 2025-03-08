#pragma once
#include <common.h>

typedef void(vector_delete)(void *);

#define GROWTH_RATE 2
#define VECTOR_DEFAULT_SIZE 10

typedef struct
{
	uint32_t size;
	char *str;
} String;

typedef struct
{
	uint64_t size;
	uint64_t element_size;
	uint64_t reserved_size;
	vector_delete *deleter;
	uint8_t *data;
} Vector;

String *string_init(char *string);
uint64_t string_size(String *string);
uint8_t string_empty(String *string);
char string_at(uint32_t index, String *string);
char *string_data(String *string);

Vector *vector_init(void *data, uint64_t element_size);
void vector_insert(void *data, Vector *vector);
void *vector_get(uint64_t index, Vector *vector);
