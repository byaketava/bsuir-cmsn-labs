package by.byak.library.mapper.book;

import by.byak.library.dto.book.BookTitleDto;
import by.byak.library.entity.Book;
import java.util.function.Function;
import org.springframework.stereotype.Component;

@Component
public class BookTitleDtoMapper implements Function<Book, BookTitleDto> {
  @Override
  public BookTitleDto apply(Book book) {
    return new BookTitleDto(book.getTitle());
  }
}
