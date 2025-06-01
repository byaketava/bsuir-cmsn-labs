package by.byak.library.mapper.book;

import by.byak.library.dto.book.BookDto;
import by.byak.library.entity.Book;
import by.byak.library.mapper.author.AuthorNameDtoMapper;
import by.byak.library.mapper.genre.GenreNameDtoMapper;
import java.util.function.Function;
import lombok.AllArgsConstructor;
import org.springframework.stereotype.Component;

@Component
@AllArgsConstructor
public class BookDtoMapper implements Function<Book, BookDto> {
  private final AuthorNameDtoMapper authorMapper = new AuthorNameDtoMapper();
  private final GenreNameDtoMapper genreMapper = new GenreNameDtoMapper();

  @Override
  public BookDto apply(Book book) {
    if (book == null) {
      return null;
    }

    BookDto bookDto = new BookDto();

    bookDto.setId(book.getId());
    bookDto.setTitle(book.getTitle());
    bookDto.setGenres(book.getGenres().stream().map(genreMapper).toList());
    bookDto.setAuthor(authorMapper.apply(book.getAuthor()));

    return bookDto;
  }
}
