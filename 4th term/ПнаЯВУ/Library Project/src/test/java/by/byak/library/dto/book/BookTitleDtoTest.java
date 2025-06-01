package by.byak.library.dto.book;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

class BookTitleDtoTest {

  @Test
  void testAllArgsConstructor() {
    BookTitleDto bookTitleDto = new BookTitleDto("Book Title");

    assertEquals("Book Title", bookTitleDto.getTitle());
  }

  @Test
  void testNoArgsConstructor() {
    BookTitleDto bookTitleDto = new BookTitleDto();

    assertNotNull(bookTitleDto);
    assertNull(bookTitleDto.getTitle());
  }

  @Test
  void testGetterAndSetter() {
    BookTitleDto bookTitleDto = new BookTitleDto();

    bookTitleDto.setTitle("Test Title");

    assertEquals("Test Title", bookTitleDto.getTitle());
  }

  @Test
  void testEqualsAndHashCode() {
    BookTitleDto bookTitleDto1 = new BookTitleDto("Test Title");
    BookTitleDto bookTitleDto2 = new BookTitleDto("Test Title");

    assertEquals(bookTitleDto1, bookTitleDto2);
    assertEquals(bookTitleDto1.hashCode(), bookTitleDto2.hashCode());
  }

  @Test
  void testToString() {
    BookTitleDto bookTitleDto = new BookTitleDto("Test Title");

    assertTrue(bookTitleDto.toString().contains("Test Title"));
  }
}
