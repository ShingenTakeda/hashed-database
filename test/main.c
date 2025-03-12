#include <database.h>

int main()
{
	UserBook *book = NULL;
	user_init_database_from_text_file("words.txt", book, 3);

	user_book_print_all_pages(book);
	return 0;
}
