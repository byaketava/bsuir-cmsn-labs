package by.byak.library.dto.genre;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNull;

class GenreNameDtoTest {

  @Test
  void testAllArgsConstructor() {
    GenreNameDto genreNameDto = new GenreNameDto("Genre Name");

    assertEquals("Genre Name", genreNameDto.getName());
  }

  @Test
  void testNoArgsConstructor() {
    GenreNameDto genreNameDto = new GenreNameDto();

    assertNotNull(genreNameDto);
    assertNull(genreNameDto.getName());
  }

  @Test
  void testSetterGetter() {
    GenreNameDto genreNameDto = new GenreNameDto();

    genreNameDto.setName("Genre Name");

    assertEquals("Genre Name", genreNameDto.getName());
  }
}
