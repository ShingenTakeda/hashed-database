#include "hash.h"

uint64_t hash(String *str)
{
	uint64_t len = str->size;
	uint32_t hash_value = 0;
	for (int i = 0; i < len; i++)
	{
		hash_value += str->str[i];
		hash_value = (hash_value * str->str[i]) % TABLE_SIZE;
	}

	return hash_value;
}
