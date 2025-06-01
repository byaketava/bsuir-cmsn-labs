package by.byak.library.dto.book;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

import by.byak.library.dto.author.AuthorNameDto;
import by.byak.library.dto.genre.GenreNameDto;
import java.util.Arrays;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.List;

class BookDtoTest {

  @Test
  void testAllArgsConstructor() {
    List<GenreNameDto> genres = new ArrayList<>();
    genres.add(new GenreNameDto("Genre 1"));
    genres.add(new GenreNameDto("Genre 2"));

    AuthorNameDto author = new AuthorNameDto("John Doe");

    BookDto bookDto = new BookDto(1L, "Book Title", genres, author);

    assertEquals(1L, bookDto.getId());
    assertEquals("Book Title", bookDto.getTitle());
    assertEquals(2, bookDto.getGenres().size());
    assertEquals("Genre 1", bookDto.getGenres().get(0).getName());
    assertEquals("Genre 2", bookDto.getGenres().get(1).getName());
    assertEquals("John Doe", bookDto.getAuthor().getName());
  }

  @Test
  void testNoArgsConstructor() {
    BookDto bookDto = new BookDto();

    assertNotNull(bookDto);
    assertNull(bookDto.getId());
    assertNull(bookDto.getTitle());
    assertNull(bookDto.getGenres());
    assertNull(bookDto.getAuthor());
  }

  @Test
  void testGettersAndSetters() {
    Long id = 1L;
    String title = "The Great Book";
    List<GenreNameDto> genres = Arrays.asList(new GenreNameDto(), new GenreNameDto());
    AuthorNameDto author = new AuthorNameDto();

    BookDto bookDto = new BookDto();
    bookDto.setId(id);
    bookDto.setTitle(title);
    bookDto.setGenres(genres);
    bookDto.setAuthor(author);

    assertEquals(id, bookDto.getId());
    assertEquals(title, bookDto.getTitle());
    assertEquals(genres, bookDto.getGenres());
    assertEquals(author, bookDto.getAuthor());
  }

  @Test
  void testEqualsAndHashCode() {
    BookDto bookDto1 = new BookDto(1L, "The Great Book", Arrays.asList(new GenreNameDto(), new GenreNameDto()), new AuthorNameDto());
    BookDto bookDto2 = new BookDto(1L, "The Great Book", Arrays.asList(new GenreNameDto(), new GenreNameDto()), new AuthorNameDto());

    assertEquals(bookDto1, bookDto2);
    assertEquals(bookDto1.hashCode(), bookDto2.hashCode());
  }

  @Test
  void testToString() {
    BookDto bookDto = new BookDto(1L, "The Great Book", Arrays.asList(new GenreNameDto(), new GenreNameDto()), new AuthorNameDto());

    String toString = bookDto.toString();

    assertNotNull(toString);
    assertTrue(toString.contains("BookDto"));
    assertTrue(toString.contains("id=1"));
    assertTrue(toString.contains("title=The Great Book"));
  }
}
