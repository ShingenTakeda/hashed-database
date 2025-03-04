#include "base_structures.h"

String *string_init(char *string)
{
	String *ptr = (String *)malloc(sizeof(String));

	if (string != NULL)
	{
		ptr->size = strlen(string);
		ptr->str = malloc(ptr->size);
		memcpy(ptr->str, string, ptr->size);
	}
	else
	{
		ptr->str = NULL;
		ptr->size = 0;
	}

	return ptr;
}

uint64_t string_size(String *string)
{
	return string->size;
}

uint8_t string_empty(String *string)
{
	if (string->size == 0)
	{
		return true;
	}

	return false;
}

char string_at(uint32_t index, String *string)
{
	if (index > string->size)
	{
		return 0;
	}

	return string->str[index];
}

char *string_data(String *string)
{
	return string->str;
}

Vector *vector_init(void *data, uint64_t element_size)
{
	Vector *ptr = malloc(sizeof(Vector));
	if (ptr != NULL)
	{
		ptr->data = (uint8_t *)calloc(VECTOR_DEFAULT_SIZE, element_size);
		ptr->element_size = element_size;
		ptr->reserved_size = element_size * VECTOR_DEFAULT_SIZE;

		if (data != NULL)
		{
			memcpy(ptr->data, data, element_size);
			ptr->size = 1;
		}
		else
		{
			ptr->size = 0;
		}

		return ptr;
	}

	return ptr;
}

void vector_insert(void *data, Vector *vector)
{
	memcpy(&vector->data[vector->element_size * vector->size], data, vector->element_size);
	if (vector->size++ >= (vector->reserved_size / vector->element_size))
	{
		vector->data = realloc(vector->data, vector->element_size * (vector->size * GROWTH_RATE));
		vector->reserved_size = vector->element_size * (vector->size * GROWTH_RATE);
	}
}

void *vector_get(uint64_t index, Vector *vector)
{
	if (index < vector->size)
	{
		return (void *)&vector->data[(vector->element_size * index)];
	}
	return NULL;
}
