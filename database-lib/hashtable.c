#include "hashtable.h"

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

void print_hash(String *string)
{
	printf("%s => %lu\n", string->str, hash(string));
}

void print_table(String **table, uint64_t size)
{
	for (int i = 0; i < size; i++)
	{
		print_hash(table[i]);
	}
}
