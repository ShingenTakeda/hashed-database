#include "base_structures.h"
#include <stdio.h>
#include <storage.h>

void print_page(Page *page)
{
	for (int i = 0; i < page->strings->size; i++)
	{
		println_s((String *)vector_get(i, page->strings));
	}
}

int main()
{
	Page *page = page_init();
	if (page == NULL)
	{
		return 1;
	}

	if (page_alloc_string("test string", page) == false)
	{
		printf("Couldn't allocate string!\n");
		return 1;
	}

	if (page_alloc_string("another string", page) == false)
	{
		printf("Couldn't allocate string!\n");
		return 1;
	}

	String *t = (String *)vector_get(0, page->strings);

	print_page(page);
	return 0;
}
