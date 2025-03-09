#include <storage.h>

int main()
{
	Book *book = book_init();
	if (book == NULL)
	{
		return 1;
	}

	book_new_page(book);
	book_write_to_page("test string", book);
	book_write_to_page("another string", book);
	book_write_to_page("and another string", book);
	book_write_to_page("now, a poem:", book);
	book_write_to_page("this thing", book);
	book_write_to_page("called love,", book);
	book_write_to_page("a wonderful thing,", book);
	book_write_to_page("a warm thing,", book);
	book_write_to_page("nothing as beautiful,", book);
	book_write_to_page("as love.", book);

	book_page_print(0, book);

	return 0;
}
