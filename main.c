#include "base_structures.h"
#include "hash.h"

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

int main()
{

	String *a = string_init("Jacob");
	String *b = string_init("Philip");

	print_hash(a);
	print_hash(b);

	return 0;
}
