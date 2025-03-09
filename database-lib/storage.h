#pragma once
#include <common.h>

// Serialize and deserialize into a binary blob
typedef struct
{
	Arena arena;	 // Store strings here
	Vector *strings; // Get string from pointer here
} Page;

typedef struct
{
	Vector *pages;
} Book;

Page *page_init();
bool page_alloc_string(char *string, Page *page);
void print_page(Page *page);

Book *book_init();
bool book_new_page(Book *book);
void book_write_to_page(char *string, Book *book);
uint64_t book_num_pages(Book *book);
Page *book_get_page(uint64_t index, Book *book);
void book_page_print(uint64_t index, Book *book);
void book_print_all_pages(Book *book);
