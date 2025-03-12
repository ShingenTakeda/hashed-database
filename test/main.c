#include "storage.h"
#include <database.h>

int main()
{
	UserBook *book = user_book_init(10);
	user_init_database_from_text_file("words.txt", book);

	user_book_print_all_pages(book);

	return 0;
}
