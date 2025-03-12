#include "storage.h"
#include <database.h>
#include <stdint.h>
#define DEFAULT_NUM_STRING 2

void init_database(Book *book)
{
	book = book_init();
	book_new_page(book);
}

void init_database_from_text_file(const char *filepath, Book *book)
{
	// Init book and allocate a page
	book = book_init();
	if (book == NULL)
	{
		printf("Could not allocate book!\n");
		exit(1);
	}

	book_new_page(book);

	String string; // To hold line pointer to buf and the size without the \n or \0
	char line_buf[256];

	FILE *file = fopen(filepath, "r");

	if (file == NULL)
	{
		fprintf(stderr, "Unable to open file\n");
		exit(1);
	}

	while (fgets(line_buf, sizeof(line_buf), file))
	{
		line_buf[strcspn(line_buf, "\n")] = 0;
		book_write_to_page(line_buf, book);
	}

	fclose(file);
}

void init_database_from_binary_file(const char *filepath, Book *book)
{
}

void user_init_database(UserBook *book, size_t num_of_string)
{
	if (num_of_string == 0)
	{
		book = user_book_init(DEFAULT_NUM_STRING);
	}
	else
	{
		book = user_book_init(num_of_string);
	}
}

void user_init_database_from_text_file(const char *filepath, UserBook *book)
{
	FILE *file = fopen(filepath, "r");
	if (file == NULL)
	{
		exit(1);
	}

	char line_buf[256];

	while (fgets(line_buf, sizeof(line_buf), file))
	{
		line_buf[strcspn(line_buf, "\n")] = '\0';
		user_book_write_to_page(line_buf, book);
	}
	fclose(file);
}

void user_init_database_from_binary_file(const char *filepath, UserBook *book, size_t num_of_string)
{
}
