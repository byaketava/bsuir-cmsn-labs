package by.byak.library.mapper.book;

import by.byak.library.dto.book.BookTitleDto;
import by.byak.library.entity.Book;
import org.junit.jupiter.api.Test;
import org.mockito.Mockito;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.mockito.Mockito.when;

class BookTitleDtoMapperTest {

  @Test
  void testBookTitleDtoMapper() {
    Book book = Mockito.mock(Book.class);
    when(book.getTitle()).thenReturn("Book Title");

    BookTitleDtoMapper mapper = new BookTitleDtoMapper();

    BookTitleDto bookTitleDto = mapper.apply(book);

    assertEquals("Book Title", bookTitleDto.getTitle());
  }
}
