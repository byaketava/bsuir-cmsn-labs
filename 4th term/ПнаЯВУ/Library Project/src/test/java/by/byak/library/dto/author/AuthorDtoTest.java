package by.byak.library.dto.author;

import by.byak.library.dto.book.BookTitleDto;
import java.util.Arrays;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

class AuthorDtoTest {

  @Test
  void testAllArgsConstructor() {
    List<BookTitleDto> books = new ArrayList<>();
    books.add(new BookTitleDto("Book 1"));
    books.add(new BookTitleDto("Book 2"));

    AuthorDto authorDto = new AuthorDto(1L, "John Doe", books);

    assertEquals(1L, authorDto.getId());
    assertEquals("John Doe", authorDto.getName());
    assertEquals(2, authorDto.getBooks().size());
    assertEquals("Book 1", authorDto.getBooks().get(0).getTitle());
    assertEquals("Book 2", authorDto.getBooks().get(1).getTitle());
  }

  @Test
  void testNoArgsConstructor() {
    AuthorDto authorDto = new AuthorDto();

    assertNotNull(authorDto);
    assertNull(authorDto.getId());
    assertNull(authorDto.getName());
    assertNull(authorDto.getBooks());
  }

  @Test
  void testSetterGetter() {
    AuthorDto authorDto = new AuthorDto();

    authorDto.setId(1L);
    authorDto.setName("John Doe");

    List<BookTitleDto> books = new ArrayList<>();
    books.add(new BookTitleDto("Book 1"));
    books.add(new BookTitleDto("Book 2"));

    authorDto.setBooks(books);

    assertEquals(1L, authorDto.getId());
    assertEquals("John Doe", authorDto.getName());
    assertEquals(2, authorDto.getBooks().size());
    assertEquals("Book 1", authorDto.getBooks().get(0).getTitle());
    assertEquals("Book 2", authorDto.getBooks().get(1).getTitle());
  }

  @Test
  void testEqualsAndHashCode() {
    AuthorDto authorDto1 = new AuthorDto(1L, "John Doe", Arrays.asList(new BookTitleDto(), new BookTitleDto()));
    AuthorDto authorDto2 = new AuthorDto(1L, "John Doe", Arrays.asList(new BookTitleDto(), new BookTitleDto()));

    assertEquals(authorDto1, authorDto2);
    assertEquals(authorDto1.hashCode(), authorDto2.hashCode());
  }

  @Test
  void testToString() {
    AuthorDto authorDto = new AuthorDto(1L, "John Doe", Arrays.asList(new BookTitleDto(), new BookTitleDto()));

    String toString = authorDto.toString();

    assertNotNull(toString);
    assertTrue(toString.contains("AuthorDto"));
    assertTrue(toString.contains("id=1"));
    assertTrue(toString.contains("name=John Doe"));
  }
}
