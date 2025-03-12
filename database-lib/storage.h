#pragma once
#include "allocators.h"
#include "base_structures.h"
#include <common.h>

// Serialize and deserialize into a binary blob
typedef struct
{
	Arena arena;	 // Store strings here
	Vector *strings; // Get string from pointer here
} Page;

typedef struct
{
	Vector *strings;
} UserPage;

typedef struct
{
	Vector *pages;
} Book;

typedef struct
{
	Vector *pages;
	uint8_t strings_per_page;
} UserBook;

Page *page_init();
bool page_alloc_string(char *string, Page *page);
void print_page(Page *page);

UserPage *user_page_init();
bool user_page_alloc_string(char *string, UserPage *page);
void user_print_page(UserPage *page);

Book *book_init();
bool book_new_page(Book *book);
void book_write_to_page(char *string, Book *book);
uint64_t book_num_pages(Book *book);
Page *book_get_page(uint64_t index, Book *book);
void book_page_print(uint64_t index, Book *book);
void book_print_all_pages(Book *book);

UserBook *user_book_init(uint8_t string_per_page);
bool user_book_new_page(UserBook *book);
void user_book_write_to_page(char *string, UserBook *book);
uint64_t user_book_num_pages(UserBook *book);
UserPage *user_book_get_page(uint64_t index, UserBook *book);
void user_book_page_print(uint64_t index, UserBook *book);
void user_book_print_all_pages(UserBook *book);
