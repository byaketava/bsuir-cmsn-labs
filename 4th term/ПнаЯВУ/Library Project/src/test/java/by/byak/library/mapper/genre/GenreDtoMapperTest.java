package by.byak.library.mapper.genre;

import by.byak.library.dto.genre.GenreDto;
import by.byak.library.entity.Book;
import by.byak.library.entity.Genre;
import org.junit.jupiter.api.Test;
import org.mockito.Mockito;

import java.util.Arrays;
import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.mockito.Mockito.when;

class GenreDtoMapperTest {

  @Test
  void testGenreDtoMapper() {
    Book book1 = Mockito.mock(Book.class);
    when(book1.getTitle()).thenReturn("Book 1");
    Book book2 = Mockito.mock(Book.class);
    when(book2.getTitle()).thenReturn("Book 2");
    List<Book> books = Arrays.asList(book1, book2);

    Genre genre = Mockito.mock(Genre.class);
    when(genre.getId()).thenReturn(1L);
    when(genre.getName()).thenReturn("Genre Name");
    when(genre.getBooks()).thenReturn(books);

    GenreDtoMapper mapper = new GenreDtoMapper();

    GenreDto genreDto = mapper.apply(genre);

    assertEquals(1L, genreDto.getId());
    assertEquals("Genre Name", genreDto.getName());
    assertEquals(2, genreDto.getBooks().size());
    assertEquals("Book 1", genreDto.getBooks().get(0).getTitle());
    assertEquals("Book 2", genreDto.getBooks().get(1).getTitle());
  }
}
