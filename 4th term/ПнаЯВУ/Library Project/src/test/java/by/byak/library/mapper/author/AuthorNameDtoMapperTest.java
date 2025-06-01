package by.byak.library.mapper.author;

import by.byak.library.dto.author.AuthorNameDto;
import by.byak.library.entity.Author;
import org.junit.jupiter.api.Test;
import org.mockito.Mockito;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.mockito.Mockito.when;

class AuthorNameDtoMapperTest {

  @Test
  void testAuthorNameDtoMapper() {
    Author author = Mockito.mock(Author.class);
    when(author.getName()).thenReturn("John Doe");

    AuthorNameDtoMapper mapper = new AuthorNameDtoMapper();

    AuthorNameDto authorNameDto = mapper.apply(author);

    assertEquals("John Doe", authorNameDto.getName());
  }
}