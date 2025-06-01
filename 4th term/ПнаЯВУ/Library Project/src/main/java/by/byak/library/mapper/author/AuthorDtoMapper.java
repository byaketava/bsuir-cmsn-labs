package by.byak.library.mapper.author;

import by.byak.library.dto.author.AuthorDto;
import by.byak.library.dto.book.BookTitleDto;
import by.byak.library.entity.Author;
import java.util.List;
import java.util.function.Function;
import org.springframework.stereotype.Component;

@Component
public class AuthorDtoMapper implements Function<Author, AuthorDto> {
  @Override
  public AuthorDto apply(Author author) {
    List<BookTitleDto> bookTitles = author.getBooks().stream()
        .map(book -> new BookTitleDto(book.getTitle())).toList();

    return new AuthorDto(author.getId(), author.getName(), bookTitles);
  }
}
