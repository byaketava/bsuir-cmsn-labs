package by.byak.library.mapper.author;

import by.byak.library.dto.author.AuthorNameDto;
import by.byak.library.entity.Author;
import java.util.function.Function;
import org.springframework.stereotype.Component;

@Component
public class AuthorNameDtoMapper implements Function<Author, AuthorNameDto> {
  @Override
  public AuthorNameDto apply(Author author) {
    return new AuthorNameDto(author.getName());
  }
}
