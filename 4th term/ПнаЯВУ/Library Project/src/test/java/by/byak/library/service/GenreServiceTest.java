package by.byak.library.service;

import by.byak.library.cache.InMemoryCache;
import by.byak.library.dto.genre.GenreDto;
import by.byak.library.entity.Book;
import by.byak.library.entity.Genre;
import by.byak.library.exception.AlreadyExistsException;
import by.byak.library.exception.BadRequestException;
import by.byak.library.exception.NotFoundException;
import by.byak.library.mapper.genre.GenreDtoMapper;
import by.byak.library.repository.GenreRepository;
import by.byak.library.repository.BookRepository;
import java.util.ArrayList;
import java.util.Collections;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;
import java.util.List;
import java.util.Optional;
import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.Mockito.*;

class GenreServiceTest {

  @Mock
  private GenreRepository genreRepository;

  @Mock
  private BookRepository bookRepository;

  @Mock
  private GenreDtoMapper genreMapper;

  @Mock
  private InMemoryCache<Integer, Genre> cache;

  @InjectMocks
  private GenreService genreService;

  @BeforeEach
  void setUp() {
    MockitoAnnotations.openMocks(this);
  }

  @Test
  void testFindAllGenresSuccess() {
    Genre genre1 = new Genre();
    Genre genre2 = new Genre();
    List<Genre> genres = List.of(genre1, genre2);
    when(genreRepository.findAll()).thenReturn(genres);
    GenreDto genreDto1 = new GenreDto();
    GenreDto genreDto2 = new GenreDto();
    when(genreMapper.apply(any(Genre.class))).thenReturn(genreDto1, genreDto2);

    List<GenreDto> result = genreService.findAllGenres();

    assertEquals(2, result.size());
    assertTrue(result.contains(genreDto1));
    assertTrue(result.contains(genreDto2));
    verify(genreRepository, times(1)).findAll();
  }

  @Test
  void testFindAllGenres_EmptyList() {
    when(genreRepository.findAll()).thenReturn(List.of());

    List<GenreDto> result = genreService.findAllGenres();

    assertTrue(result.isEmpty());
    verify(genreRepository, times(1)).findAll();
  }

  @Test
  void testFindAllGenres_ExceptionHandling() {
    when(genreRepository.findAll()).thenThrow(new RuntimeException("Test exception"));

    assertThrows(RuntimeException.class, () -> genreService.findAllGenres());
    verify(genreRepository, times(1)).findAll();
  }

  @Test
  void testFindAllGenresOneGenre() {
    List<Genre> genres = Collections.singletonList(new Genre());
    genres.get(0).setName("Fantasy");
    when(genreRepository.findAll()).thenReturn(genres);
    when(genreMapper.apply(any(Genre.class))).thenReturn(
        new GenreDto(1L, "Fantasy", new ArrayList<>()));

    List<GenreDto> result = genreService.findAllGenres();

    assertEquals(1, result.size());
    assertEquals("Fantasy", result.get(0).getName());
    verify(genreRepository, times(1)).findAll();
    verify(genreMapper, times(1)).apply(any(Genre.class));
  }

  @Test
  void testFindGenreByName_GenreInCache() {
    String name = "Test Genre";
    Genre cachedGenre = new Genre();
    cachedGenre.setName(name);
    GenreDto genreDto = new GenreDto();

    when(cache.get(name.hashCode())).thenReturn(cachedGenre);
    when(genreMapper.apply(cachedGenre)).thenReturn(genreDto);

    GenreDto result = genreService.findGenreByName(name);

    assertEquals(genreDto, result);
    verify(cache, times(1)).get(name.hashCode());
    verify(genreMapper, times(1)).apply(cachedGenre);
  }

  @Test
  void testFindGenreByName_GenreNotFoundInCache() {
    String name = "Test Genre";
    Genre genre = new Genre();
    GenreDto genreDto = new GenreDto();

    when(cache.get(name.hashCode())).thenReturn(null);
    when(genreRepository.findByName(name)).thenReturn(Optional.of(genre));
    when(genreMapper.apply(genre)).thenReturn(genreDto);

    GenreDto result = genreService.findGenreByName(name);

    assertEquals(genreDto, result);
    verify(genreRepository, times(1)).findByName(name);
    verify(genreMapper, times(1)).apply(genre);
  }

  @Test
  void testFindGenreByName_GenreNotFoundInRepository() {
    String name = "Test Genre";

    when(cache.get(name.hashCode())).thenReturn(null);
    when(genreRepository.findByName(name)).thenReturn(Optional.empty());

    assertThrows(NotFoundException.class, () -> genreService.findGenreByName(name));

    verify(genreRepository, times(1)).findByName(name);
  }

  @Test
  void testFindGenreByName_ExceptionHandling() {
    String genreName = "Test Genre";
    when(cache.get(genreName.hashCode())).thenReturn(null);
    when(genreRepository.findByName(genreName)).thenThrow(new RuntimeException("Test exception"));

    assertThrows(RuntimeException.class, () -> genreService.findGenreByName(genreName));
    verify(genreRepository, times(1)).findByName(genreName);
  }

  @Test
  void testAddGenreAlreadyExists() {
    String genreName = "Fantasy";
    Genre genre = new Genre();
    genre.setName(genreName);
    when(genreRepository.existsByName(genreName)).thenReturn(true);

    assertThrows(AlreadyExistsException.class, () -> genreService.addGenre(genre));
    verify(genreRepository, times(1)).existsByName(genreName);
    verify(genreRepository, never()).save(any(Genre.class));
  }

  @Test
  void testAddGenreSuccess() {
    String genreName = "Mystery";
    Genre genre = new Genre();
    genre.setName(genreName);
    when(genreRepository.existsByName(genreName)).thenReturn(false);

    genreService.addGenre(genre);

    verify(genreRepository, times(1)).existsByName(genreName);
    verify(genreRepository, times(1)).save(genre);
  }

  @Test
  void testAddGenreSaveException() {
    String genreName = "Thriller";
    Genre genre = new Genre();
    genre.setName(genreName);
    when(genreRepository.existsByName(genreName)).thenReturn(false);
    doThrow(RuntimeException.class).when(genreRepository).save(genre);

    assertThrows(BadRequestException.class, () -> genreService.addGenre(genre));
    verify(genreRepository, times(1)).existsByName(genreName);
    verify(genreRepository, times(1)).save(genre);
  }

  @Test
  void testDeleteGenreByIdSuccess() {
    Long genreId = 1L;
    Genre genre = new Genre();
    genre.setName(" Test Genre");
    genre.setId(genreId);
    Book book = new Book();
    book.setTitle("Test Book");
    genre.setBooks(Collections.singletonList(book));

    when(genreRepository.findById(genreId)).thenReturn(Optional.of(genre));
    when(bookRepository.save(any(Book.class))).thenReturn(book);

    genreService.deleteGenreById(genreId);

    verify(genreRepository, times(1)).findById(genreId);
    verify(bookRepository, times(1)).save(book);
    verify(genreRepository, times(1)).delete(genre);
  }

  @Test
  void testDeleteGenreById_GenreNotFound() {
    Long genreId = 1L;
    when(genreRepository.findById(genreId)).thenReturn(Optional.empty());

    assertThrows(NotFoundException.class, () -> genreService.deleteGenreById(genreId));
    verify(genreRepository, times(1)).findById(genreId);
  }

  @Test
  void testDeleteGenreById_NotFoundException() {
    Long genreId = 1L;
    when(genreRepository.findById(genreId)).thenReturn(Optional.empty());

    assertThrows(NotFoundException.class, () -> genreService.deleteGenreById(genreId));

    verify(genreRepository, times(1)).findById(genreId);
  }

  @Test
  void testDeleteGenreById_BadRequestException() {
    Long genreId = 1L;
    Genre genre = new Genre();
    genre.setName("Test Genre");
    Book book = new Book();
    book.setTitle("Test Book");
    genre.setBooks(Collections.singletonList(book));

    when(genreRepository.findById(genreId)).thenReturn(Optional.of(genre));
    when(bookRepository.save(any(Book.class))).thenThrow(new RuntimeException("Save failed"));

    assertThrows(BadRequestException.class, () -> genreService.deleteGenreById(genreId));

    verify(genreRepository, times(1)).findById(genreId);
    verify(bookRepository, times(1)).save(book);
  }

  @Test
  void testUpdateGenre_GenreExists() {
    Long id = 1L;
    Genre genre = new Genre();
    genre.setId(id);
    genre.setName("Updated Genre");
    Book book1 = new Book();
    genre.setBooks(List.of(book1));

    Genre existingGenre = new Genre();
    existingGenre.setName("Old Genre");

    when(genreRepository.findById(id)).thenReturn(Optional.of(existingGenre));

    genreService.updateGenre(id, genre);

    verify(genreRepository, times(1)).save(existingGenre);
  }

  @Test
  void testUpdateGenre_GenreNotFound() {
    Long id = 1L;
    Genre genre = new Genre();
    genre.setName("Updated Genre");

    when(genreRepository.findById(id)).thenReturn(Optional.empty());

    assertThrows(NotFoundException.class, () -> genreService.updateGenre(id, genre));

    verify(genreRepository, times(1)).findById(id);
  }

  @Test
  void testUpdateGenre_ExceptionDuringSave() {
    Long id = 1L;
    Genre genre = new Genre();
    genre.setName("Updated Genre");
    Book book1 = new Book();
    genre.setBooks(List.of(book1));

    Genre existingGenre = new Genre();
    existingGenre.setName("Old Genre");

    when(genreRepository.findById(id)).thenReturn(Optional.of(existingGenre));
    doThrow(new RuntimeException("Save failed")).when(genreRepository).save(existingGenre);

    assertThrows(BadRequestException.class, () -> genreService.updateGenre(id, genre));

    verify(cache, times(1)).remove(existingGenre.getName().hashCode());
    verify(genreRepository, times(1)).save(existingGenre);
  }
}
