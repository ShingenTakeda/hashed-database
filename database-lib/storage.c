#include "storage.h"
#include "allocators.h"
#include "base_structures.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

Page *page_init_by_user(uint8_t *mem_buffer, size_t buffer_len)
{
	Page *ptr = calloc(1, sizeof(Page));

	if (ptr != NULL)
	{
		arena_init(&ptr->arena, mem_buffer, buffer_len);
		ptr->strings = vector_init(NULL, sizeof(String));
		return ptr;
	}

	return NULL;
}

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

void book_write_to_page_at(uint64_t index, char *string, Book *book)
{
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

UserPage *user_page_init()
{
	UserPage *ptr = calloc(1, sizeof(Page));

	if (ptr != NULL)
	{
		ptr->strings = vector_init(NULL, sizeof(String));

		return ptr;
	}

	return NULL;
}

bool user_page_alloc_string(char *string, UserPage *page)
{
	String vec_string;
	vector_insert(&vec_string, page->strings);
	String *str_ptr = (String *)vector_get(page->strings->size - 1, page->strings);
	str_ptr->size = strlen(string);
	str_ptr->str = malloc(strlen(string));

	if (str_ptr->str != NULL)
	{
		memmove(str_ptr->str, string, str_ptr->size);
		return true;
	}

	return false;
}

void user_print_page(UserPage *page)
{
	String *s = NULL;
	for (int i = 0; i < page->strings->size; i++)
	{
		s = (String *)vector_get(i, page->strings);
		println_s(s);
	}
}

UserBook *user_book_init(uint8_t strings_per_page)
{
	UserBook *ptr = malloc(sizeof(UserBook));
	if (ptr == NULL)
	{
		return NULL;
	}

	ptr->pages = vector_init(NULL, sizeof(UserPage));
	if (ptr->pages == NULL)
	{
		return NULL;
	}

	if (user_book_new_page(ptr) == false)
	{
		return NULL;
	}

	ptr->strings_per_page = strings_per_page;

	return ptr;
}

bool user_book_new_page(UserBook *book)
{
	UserPage *ptr = user_page_init();

	if (ptr == NULL)
	{
		return false;
	}
	vector_insert(ptr, book->pages);

	free(ptr);

	return true;
}

void user_book_write_to_page(char *string, UserBook *book)
{
	UserPage *p_ptr = (UserPage *)vector_get(book->pages->size - 1, book->pages);
	if (p_ptr->strings->size == book->strings_per_page)
	{
		user_book_new_page(book);
		p_ptr = (UserPage *)vector_get(book->pages->size - 1, book->pages);
		user_page_alloc_string(string, p_ptr);
	}
	else
	{
		user_page_alloc_string(string, p_ptr);
	}
}

uint64_t user_book_num_pages(UserBook *book)
{
	return book->pages->size;
}

UserPage *user_book_get_page(uint64_t index, UserBook *book)
{
	if (index > book->pages->size - 1)
	{
		return NULL;
	}
	return (UserPage *)vector_get(index, book->pages);
}

void user_book_page_print(uint64_t index, UserBook *book)
{
	UserPage *ptr = user_book_get_page(index, book);
	user_print_page(ptr);
}

void user_book_print_all_pages(UserBook *book)
{
	for (uint64_t i = 0; i < book->pages->size; i++)
	{
		printf("page number: %lu\n", i);
		user_book_page_print(i, book);
	}
}
