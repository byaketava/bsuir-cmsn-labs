package by.byak.library.repository;

import by.byak.library.entity.Genre;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;
import java.util.Optional;

import static org.mockito.Mockito.*;

class GenreRepositoryTest {

  @Mock
  private GenreRepository genreRepository;

  @BeforeEach
  void setup() {
    MockitoAnnotations.openMocks(this);
  }

  @Test
  void testFindByName() {
    String genreName = "Mystery";
    Genre genre = new Genre();
    genre.setName(genreName);
    when(genreRepository.findByName(genreName)).thenReturn(Optional.of(genre));

    Optional<Genre> result = genreRepository.findByName(genreName);

    Assertions.assertTrue(result.isPresent());
    Assertions.assertEquals(genre, result.get());

    verify(genreRepository, times(1)).findByName(genreName);
  }

  @Test
  void testExistsByName() {
    String genreName = "Mystery";
    when(genreRepository.existsByName(genreName)).thenReturn(true);

    boolean result = genreRepository.existsByName(genreName);

    Assertions.assertTrue(result);

    verify(genreRepository, times(1)).existsByName(genreName);
  }
}
