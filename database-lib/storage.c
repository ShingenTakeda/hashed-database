#include "storage.h"
#include "base_structures.h"
#include <stdio.h>
#include <sys/types.h>

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

void print_page(Page *page)
{
	for (int i = 0; i < page->strings->size; i++)
	{
		println_s((String *)vector_get(i, page->strings));
	}
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

	free(ptr);

	return true;
}

void book_write_to_page(char *string, Book *book)
{
	bool test = page_alloc_string(string, vector_get(book->pages->size - 1, book->pages));

	if (test == false)
	{
		test = book_new_page(book);
		if (test == false)
		{
			printf("Failed to allocate page to book\n");
			exit(1);
		}

		test = page_alloc_string(string, vector_get(book->pages->size - 1, book->pages));
		if (test == false)
		{
			printf("Failed to allocate string to page to book\n");
			exit(1);
		}
	}
}

void book_page_print(uint64_t index, Book *book)
{
	print_page(book_get_page(index, book));
}

void book_print_all_pages(Book *book)
{
	for (uint64_t i = 0; i < book->pages->size; i++)
	{
		printf("page number: %lu\n", i);
		book_page_print(i, book);
	}
}

uint64_t book_num_pages(Book *book)
{
	return book->pages->size;
}

Page *book_get_page(uint64_t index, Book *book)
{
	return (Page *)vector_get(index, book->pages);
}
