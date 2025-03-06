#pragma once
#include "base_structures.h"
#include "common.h"

// Serialize and deserialize into a binary blob
typedef struct
{
	Arena arena;	 // Store strings here
	Vector *strings; // Get string from pointer here
	uint64_t num_of_strings;
} Page;

typedef struct
{
	Page *page;
	uint64_t num_of_pages;
} Book;

Page *page_init(size_t size);
bool page_alloc_string(char *string, Page *page);

void book_new_page(Book *book);
uint64_t book_num_pages(Book *book);
Page *book_get_page(uint64_t index);
