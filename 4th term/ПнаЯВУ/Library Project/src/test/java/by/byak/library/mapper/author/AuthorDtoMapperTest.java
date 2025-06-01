package by.byak.library.mapper.author;

import by.byak.library.dto.author.AuthorDto;
import by.byak.library.entity.Author;
import by.byak.library.entity.Book;
import org.junit.jupiter.api.Test;
import org.mockito.Mockito;

import java.util.Arrays;
import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.mockito.Mockito.when;

class AuthorDtoMapperTest {

  @Test
  void testAuthorDtoMapper() {
    Author author = Mockito.mock(Author.class);
    when(author.getId()).thenReturn(1L);
    when(author.getName()).thenReturn("John Doe");

    Book book1 = Mockito.mock(Book.class);
    when(book1.getTitle()).thenReturn("Book 1");
    Book book2 = Mockito.mock(Book.class);
    when(book2.getTitle()).thenReturn("Book 2");
    List<Book> books = Arrays.asList(book1, book2);
    when(author.getBooks()).thenReturn(books);

    AuthorDtoMapper mapper = new AuthorDtoMapper();

    AuthorDto authorDto = mapper.apply(author);

    assertEquals(1L, authorDto.getId());
    assertEquals("John Doe", authorDto.getName());
    assertEquals(2, authorDto.getBooks().size());
    assertEquals("Book 1", authorDto.getBooks().get(0).getTitle());
    assertEquals("Book 2", authorDto.getBooks().get(1).getTitle());
  }
}
