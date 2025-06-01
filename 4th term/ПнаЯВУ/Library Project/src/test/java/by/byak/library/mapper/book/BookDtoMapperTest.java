package by.byak.library.mapper.book;

import by.byak.library.dto.book.BookDto;
import by.byak.library.entity.Author;
import by.byak.library.entity.Book;
import by.byak.library.entity.Genre;
import by.byak.library.mapper.author.AuthorNameDtoMapper;
import by.byak.library.mapper.genre.GenreNameDtoMapper;
import org.junit.jupiter.api.Test;
import org.mockito.Mockito;

import java.util.Arrays;
import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.mockito.Mockito.when;

class BookDtoMapperTest {

  @Test
  void testBookDtoMapper() {
    Author author = Mockito.mock(Author.class);
    when(author.getName()).thenReturn("John Doe");

    Genre genre1 = Mockito.mock(Genre.class);
    when(genre1.getName()).thenReturn("Genre 1");
    Genre genre2 = Mockito.mock(Genre.class);
    when(genre2.getName()).thenReturn("Genre 2");
    List<Genre> genres = Arrays.asList(genre1, genre2);

    Book book = Mockito.mock(Book.class);
    when(book.getId()).thenReturn(1L);
    when(book.getTitle()).thenReturn("Book Title");
    when(book.getGenres()).thenReturn(genres);
    when(book.getAuthor()).thenReturn(author);

    BookDtoMapper mapper = new BookDtoMapper();

    BookDto bookDto = mapper.apply(book);

    assertEquals(1L, bookDto.getId());
    assertEquals("Book Title", bookDto.getTitle());
    assertEquals(2, bookDto.getGenres().size());
    assertEquals("Genre 1", bookDto.getGenres().get(0).getName());
    assertEquals("Genre 2", bookDto.getGenres().get(1).getName());
    assertEquals("John Doe", bookDto.getAuthor().getName());
  }

  @Test
  void testApplyWithNullBook() {
    BookDtoMapper bookDtoMapper = new BookDtoMapper();

    BookDto bookDto = bookDtoMapper.apply(null);

    assertNull(bookDto);
  }
}
