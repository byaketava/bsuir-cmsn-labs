package by.byak.library.mapper.genre;

import by.byak.library.dto.genre.GenreNameDto;
import by.byak.library.entity.Genre;
import org.junit.jupiter.api.Test;
import org.mockito.Mockito;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.mockito.Mockito.when;

class GenreNameDtoMapperTest {

  @Test
  void testGenreNameDtoMapper() {
    Genre genre = Mockito.mock(Genre.class);
    when(genre.getName()).thenReturn("Genre Name");

    GenreNameDtoMapper mapper = new GenreNameDtoMapper();

    GenreNameDto genreNameDto = mapper.apply(genre);

    assertEquals("Genre Name", genreNameDto.getName());
  }
}
