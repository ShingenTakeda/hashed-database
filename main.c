#include "base_structures.h"
#include "hash.h"
#include <stdio.h>

void print_hash(String *string)
{
	printf("%s => %lu\n", string->str, hash(string));
}

int main()
{
	String *a = string_init("Jacob");

	print_hash(a);

	return 0;
}
