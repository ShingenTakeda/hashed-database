#include "storage.h"
#include "allocators.h"
#include "base_structures.h"
#include <stdlib.h>
#include <string.h>

Page *page_init()
{
	Page *ptr = calloc(1, sizeof(Page));
	void *buf = malloc(MAX_ARENA_SIZE);

	if (ptr != NULL || buf != NULL)
	{
		arena_init(&ptr->arena, buf, MAX_ARENA_SIZE); // Init arena
		ptr->strings = vector_init(NULL, sizeof(String));

		return ptr;
	}

	return NULL;
}

// TODO:Do you due diligence here and check for errors
bool page_alloc_string(char *string, Page *page)
{
	String vec_string;
	vector_insert(&vec_string, page->strings);
	String *str_ptr = (String *)vector_get(page->strings->size - 1, page->strings);
	str_ptr->size = strlen(string);
	str_ptr->str = arena_alloc(&page->arena, str_ptr->size);

	if (str_ptr->str != NULL)
	{
		// for (int i = 0; i < str_ptr->size; i++)
		//{
		//	str_ptr->str[i] = string[i];
		// }
		memmove(str_ptr->str, string, str_ptr->size);
		return true;
	}

	return false;
}

Book *book_init()
{
	Book *ptr = malloc(sizeof(Book));
	if (ptr == NULL)
	{
		return NULL;
	}

	ptr->pages = vector_init(NULL, sizeof(Page));
	if (ptr->pages == NULL)
	{
		return NULL;
	}

	return ptr;
}

bool book_new_page(Book *book)
{
	Page *ptr = page_init();

	if (ptr == NULL)
	{
		return false;
	}
	vector_insert(ptr, book->pages);

	free(ptr->arena.buf);
	free(ptr);

	return true;
}
uint64_t book_num_pages(Book *book);
Page *book_get_page(uint64_t index);
