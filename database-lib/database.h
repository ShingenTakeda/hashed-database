#pragma once
#include <common.h>
#include <storage.h>

void init_database(Book *book);
void init_database_from_text_file(const char *filepath, Book *book);
void init_database_from_binary_file(const char *filepath, Book *book);

void user_init_database(UserBook *book, size_t num_of_string);
void user_init_database_from_text_file(const char *filepath, UserBook *book, size_t num_of_string);
void user_init_database_from_binary_file(const char *filepath, UserBook *book, size_t num_of_string);
