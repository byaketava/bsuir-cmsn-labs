package by.byak.library.repository;

import by.byak.library.entity.Author;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;

import java.util.Optional;

import static org.mockito.Mockito.*;

class AuthorRepositoryTest {

  @Mock
  private AuthorRepository authorRepository;

  @BeforeEach
  void setup() {
    MockitoAnnotations.openMocks(this);
  }

  @Test
  void testFindByName() {
    String name = "F. Scott Fitzgerald";
    Author author = new Author();
    author.setName(name);
    when(authorRepository.findByName(name)).thenReturn(Optional.of(author));

    Optional<Author> result = authorRepository.findByName(name);

    Assertions.assertTrue(result.isPresent());
    Assertions.assertEquals(author, result.get());

    verify(authorRepository, times(1)).findByName(name);
  }

  @Test
  void testExistsByName() {
    String name = "F. Scott Fitzgerald";
    when(authorRepository.existsByName(name)).thenReturn(true);

    boolean result = authorRepository.existsByName(name);

    Assertions.assertTrue(result);

    verify(authorRepository, times(1)).existsByName(name);
  }
}
