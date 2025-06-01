package by.byak.library.mapper.genre;

import by.byak.library.dto.genre.GenreNameDto;
import by.byak.library.entity.Genre;
import java.util.function.Function;
import org.springframework.stereotype.Component;

@Component
public class GenreNameDtoMapper implements Function<Genre, GenreNameDto> {
  @Override
  public GenreNameDto apply(Genre genre) {
    return new GenreNameDto(genre.getName());
  }
}
