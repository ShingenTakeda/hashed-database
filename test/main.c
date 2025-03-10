#include <database.h>

int main()
{
	Book *book = book_init();
	book_new_page(book);

	// init_database_from_text_file("words.txt", book);

	book_write_to_page("a", book);
	book_write_to_page("a", book);
	book_write_to_page("a", book);
	book_write_to_page("a", book);
	book_write_to_page("a", book);
	book_write_to_page("a", book);
	book_write_to_page("a", book);
	book_write_to_page("a", book);

	book_print_all_pages(book);

	return 0;
}
