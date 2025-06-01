package by.byak.library.dto.author;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNull;

class AuthorNameDtoTest {

  @Test
  void testAllArgsConstructor() {
    AuthorNameDto authorNameDto = new AuthorNameDto("John Doe");

    assertEquals("John Doe", authorNameDto.getName());
  }

  @Test
  void testNoArgsConstructor() {
    AuthorNameDto authorNameDto = new AuthorNameDto();

    assertNotNull(authorNameDto);
    assertNull(authorNameDto.getName());
  }

  @Test
  void testSetterGetter() {
    AuthorNameDto authorNameDto = new AuthorNameDto();

    authorNameDto.setName("John Doe");

    assertEquals("John Doe", authorNameDto.getName());
  }
}
