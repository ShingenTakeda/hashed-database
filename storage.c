#include "storage.h"
#include "allocators.h"
#include "base_structures.h"

Page *page_init(size_t size)
{
	Page *ptr = calloc(1, sizeof(Page));
	arena_init(&ptr->arena, malloc(MAX_ARENA_SIZE), MAX_ARENA_SIZE); // Init arena
	ptr->strings = vector_init(NULL, sizeof(String));
	return ptr;
}

// TODO:Do you due diligence here and check for errors
bool page_alloc_string(char *string, Page *page)
{
	String vec_string;
	vector_insert(&vec_string, page->strings);
	String *str_ptr = (String *)vector_get(page->strings->size - 1, page->strings);
	str_ptr->size = strlen(string);
	str_ptr->str = arena_alloc(&page->arena, str_ptr->size);
	memmove(str_ptr->str, string, strlen(string));

	return true;
}

void book_init(const char *filepath, Book *book)
{
}

void book_new_page(Book *book);
uint64_t book_num_pages(Book *book);
Page *book_get_page(uint64_t index);
