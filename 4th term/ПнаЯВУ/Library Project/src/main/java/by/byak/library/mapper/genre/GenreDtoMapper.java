package by.byak.library.mapper.genre;

import by.byak.library.dto.book.BookTitleDto;
import by.byak.library.dto.genre.GenreDto;
import by.byak.library.entity.Genre;
import java.util.List;
import java.util.function.Function;
import org.springframework.stereotype.Component;

@Component
public class GenreDtoMapper implements Function<Genre, GenreDto> {
  @Override
  public GenreDto apply(Genre genre) {
    List<BookTitleDto> bookTitles = genre.getBooks().stream()
        .map(book -> new BookTitleDto(book.getTitle())).toList();

    return new GenreDto(genre.getId(), genre.getName(), bookTitles);
  }
}
