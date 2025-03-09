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

	// Page *page = vector_get(0, book->pages);

	// String *s1 = (String *)vector_get(0, page->strings);
	// String *s2 = (String *)vector_get(1, page->strings);
	// String *s3 = (String *)vector_get(2, page->strings);
	// String *s4 = (String *)vector_get(3, page->strings);

	// printf("s1: %s\n", s1->str);
	// printf("s2: %s\n", s2->str);
	// printf("s3: %s\n", s3->str);
	// printf("s4: %s\n", s4->str);

	book_page_print(0, book);

	return 0;
}
