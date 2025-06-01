/*
package by.byak.library.controller;

import by.byak.library.dto.genre.GenreDto;
import by.byak.library.entity.Genre;
import by.byak.library.service.GenreService;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;

import java.util.ArrayList;
import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.mockito.Mockito.*;

class GenreControllerTest {

  private GenreController genreController;

  @Mock
  private GenreService genreService;

  @BeforeEach
  public void setup() {
    MockitoAnnotations.openMocks(this);
    genreController = new GenreController(genreService);
  }

  @Test
  void testFindAllGenres() {
    List<GenreDto> genres = new ArrayList<>();
    when(genreService.findAllGenres()).thenReturn(genres);

    ResponseEntity<List<GenreDto>> response = genreController.findAllGenres();

    verify(genreService, times(1)).findAllGenres();
    assertEquals(HttpStatus.OK, response.getStatusCode());
    assertEquals(genres, response.getBody());
  }

  @Test
  void testFindGenreByName() {
    String name = "Test Genre";

    GenreDto genreDto = new GenreDto();
    when(genreService.findGenreByName(name)).thenReturn(genreDto);

    ResponseEntity<GenreDto> response = genreController.findGenreByName(name);

    verify(genreService, times(1)).findGenreByName(name);
    assertEquals(HttpStatus.OK, response.getStatusCode());
    assertEquals(genreDto, response.getBody());
  }

  @Test
  void testAddGenre() {
    Genre genre = new Genre();

    ResponseEntity<String> response = genreController.addGenre(genre);

    verify(genreService, times(1)).addGenre(genre);
    assertEquals(HttpStatus.CREATED, response.getStatusCode());
    assertEquals("Completed successfully", response.getBody());
  }

  @Test
  void testDeleteGenreById() {
    Long id = 1L;

    ResponseEntity<String> response = genreController.deleteGenreById(id);

    verify(genreService, times(1)).deleteGenreById(id);
    assertEquals(HttpStatus.OK, response.getStatusCode());
    assertEquals("Completed successfully", response.getBody());
  }

  @Test
  void testUpdateGenre() {
    Long id = 1L;
    Genre genre = new Genre();

    ResponseEntity<String> response = genreController.updateGenre(id, genre);

    verify(genreService, times(1)).updateGenre(id, genre);
    assertEquals(HttpStatus.OK, response.getStatusCode());
    assertEquals("Completed successfully", response.getBody());
  }
}
*/
