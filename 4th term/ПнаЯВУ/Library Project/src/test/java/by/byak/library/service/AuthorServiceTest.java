package by.byak.library.service;

import by.byak.library.cache.InMemoryCache;
import by.byak.library.dto.author.AuthorDto;
import by.byak.library.entity.Author;
import by.byak.library.entity.Book;
import by.byak.library.exception.AlreadyExistsException;
import by.byak.library.exception.BadRequestException;
import by.byak.library.exception.NotFoundException;
import by.byak.library.mapper.author.AuthorDtoMapper;
import by.byak.library.repository.AuthorRepository;
import java.util.Arrays;
import java.util.Collections;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.ArgumentMatchers.any;
import static org.mockito.Mockito.*;

class AuthorServiceTest {

  @Mock
  private AuthorRepository authorRepository;

  @Mock
  private AuthorDtoMapper authorMapper;

  @Mock
  private InMemoryCache<Integer, Author> cache;

  @InjectMocks
  private AuthorService authorService;

  @BeforeEach
  void setUp() {
    MockitoAnnotations.openMocks(this);
  }

  @Test
  void testFindAllAuthors() {
    Author author1 = new Author();
    author1.setName("Author 1");

    Author author2 = new Author();
    author2.setName("Author 2");

    List<Author> authorList = new ArrayList<>();
    authorList.add(author1);
    authorList.add(author2);

    AuthorDto authorDto1 = new AuthorDto();
    authorDto1.setName("Author 1 DTO");

    AuthorDto authorDto2 = new AuthorDto();
    authorDto2.setName("Author 2 DTO");

    List<AuthorDto> authorDtoList = new ArrayList<>();
    authorDtoList.add(authorDto1);
    authorDtoList.add(authorDto2);

    when(authorRepository.findAll()).thenReturn(authorList);

    when(authorMapper.apply(author1)).thenReturn(authorDto1);
    when(authorMapper.apply(author2)).thenReturn(authorDto2);

    List<AuthorDto> result = authorService.findAllAuthors();

    assertEquals(authorDtoList.size(), result.size());
    assertTrue(result.contains(authorDto1));
    assertTrue(result.contains(authorDto2));

    verify(authorRepository, times(1)).findAll();

    verify(authorMapper, times(1)).apply(author1);
    verify(authorMapper, times(1)).apply(author2);
  }

  @Test
  void testFindByName_AuthorInCache() {
    String name = "Test Author";
    Author cachedAuthor = new Author();
    AuthorDto authorDto = new AuthorDto();

    when(cache.get(name.hashCode())).thenReturn(cachedAuthor);
    when(authorMapper.apply(cachedAuthor)).thenReturn(authorDto);

    AuthorDto result = authorService.findByName(name);

    assertEquals(authorDto, result);
    verify(cache, times(1)).get(name.hashCode());
    verify(authorMapper, times(1)).apply(cachedAuthor);
  }

  @Test
  void testFindByName_AuthorNotFoundInCache() {
    String name = "Test Author";
    Author author = new Author();
    AuthorDto authorDto = new AuthorDto();

    when(cache.get(name.hashCode())).thenReturn(null);
    when(authorRepository.findByName(name)).thenReturn(Optional.of(author));
    when(authorMapper.apply(author)).thenReturn(authorDto);

    AuthorDto result = authorService.findByName(name);

    assertEquals(authorDto, result);
    verify(cache, times(1)).get(name.hashCode());
    verify(authorRepository, times(1)).findByName(name);
    verify(authorMapper, times(1)).apply(author);
  }

  @Test
  void testFindByName_AuthorNotFoundInRepository() {
    String name = "Test Author";

    when(cache.get(name.hashCode())).thenReturn(null);
    when(authorRepository.findByName(name)).thenReturn(Optional.empty());

    assertThrows(NotFoundException.class, () -> authorService.findByName(name));

    verify(cache, times(1)).get(name.hashCode());
    verify(authorRepository, times(1)).findByName(name);
  }

  @Test
  void testAddAuthor() {
    Author author = new Author();
    author.setName("Test Author");

    when(authorRepository.existsByName("Test Author")).thenReturn(false);

    authorService.addAuthor(author);

    verify(authorRepository, times(1)).existsByName("Test Author");
    verify(authorRepository, times(1)).save(author);
  }

  @Test
  void testAddAuthor_ExceptionDuringSave() {
    Author author = new Author();
    author.setName("Test Author");

    when(authorRepository.existsByName(author.getName())).thenReturn(false);

    doThrow(new RuntimeException("Save failed")).when(authorRepository).save(author);

    assertThrows(InternalError.class, () -> authorService.addAuthor(author));

    verify(authorRepository, times(1)).save(author);
  }

  @Test
  void testAddAuthor_AlreadyExists() {
    Author author = new Author();
    author.setName("Test Author");

    when(authorRepository.existsByName("Test Author")).thenReturn(true);

    assertThrows(AlreadyExistsException.class, () -> authorService.addAuthor(author));

    verify(authorRepository, times(1)).existsByName("Test Author");
    verify(authorRepository, never()).save(author);
  }

  @Test
  void testAddAuthor_AuthorDoesNotExist() {
    Author author = new Author();
    author.setName("Test Author");

    when(authorRepository.existsByName(author.getName())).thenReturn(false);

    authorService.addAuthor(author);

    verify(authorRepository, times(1)).save(author);
  }

  @Test
  void testDeleteAuthorById() {
    Author author = new Author();
    author.setId(1L);
    author.setName("Test Author");

    when(authorRepository.findById(1L)).thenReturn(Optional.of(author));

    authorService.deleteAuthorById(1L);

    verify(authorRepository, times(1)).findById(1L);
    verify(authorRepository, times(1)).delete(author);

    verify(cache, times(1)).remove(author.getName().hashCode());
  }

  @Test
  void testDeleteAuthorById_NotFound() {
    when(authorRepository.findById(1L)).thenReturn(Optional.empty());

    assertThrows(NotFoundException.class, () -> authorService.deleteAuthorById(1L));

    verify(authorRepository, times(1)).findById(1L);
    verify(authorRepository, never()).delete(any());

    verify(cache, never()).remove(anyInt());
  }

  @Test
  void testUpdateAuthor_AuthorExists() {
    Long id = 1L;
    Author author = new Author();
    author.setName("Updated Name");
    author.setBooks(Collections.singletonList(new Book()));

    Author existingAuthor = new Author();
    existingAuthor.setName("Old Name");
    existingAuthor.setBooks(Collections.singletonList(new Book()));

    when(authorRepository.findById(id)).thenReturn(Optional.of(existingAuthor));

    authorService.updateAuthor(id, author);

    assertEquals(author.getName(), existingAuthor.getName());
    assertEquals(author.getBooks(), existingAuthor.getBooks());
    verify(cache, times(1)).remove(author.getName().hashCode());
    verify(authorRepository, times(1)).save(existingAuthor);
  }

  @Test
  void testUpdateAuthor_NotFound() {
    Author updatedAuthor = new Author();
    updatedAuthor.setName("Updated Author");

    when(authorRepository.findById(1L)).thenReturn(Optional.empty());

    assertThrows(NotFoundException.class, () -> authorService.updateAuthor(1L, updatedAuthor));

    verify(authorRepository, times(1)).findById(1L);
    verify(authorRepository, never()).save(any());

    verify(cache, never()).remove(anyInt());
  }

  @Test
  void testUpdateAuthor_BooksAuthorSetCorrectly() {
    Long id = 1L;
    Author author = new Author();
    author.setName("Updated Name");
    Book book1 = new Book();
    Book book2 = new Book();
    author.setBooks(Arrays.asList(book1, book2));

    Author existingAuthor = new Author();
    existingAuthor.setName("Old Name");

    when(authorRepository.findById(id)).thenReturn(Optional.of(existingAuthor));

    authorService.updateAuthor(id, author);

    assertEquals(existingAuthor, book1.getAuthor());
    assertEquals(existingAuthor, book2.getAuthor());
    verify(cache, times(1)).remove(author.getName().hashCode());
    verify(authorRepository, times(1)).save(existingAuthor);
  }

  @Test
  void testUpdateAuthor_ExceptionDuringSave() {
    Long id = 1L;
    Author author = new Author();
    author.setName("Updated Name");

    Author existingAuthor = new Author();
    existingAuthor.setName("Old Name");

    when(authorRepository.findById(id)).thenReturn(Optional.of(existingAuthor));
    doThrow(new RuntimeException("Save failed")).when(authorRepository).save(existingAuthor);

    assertThrows(BadRequestException.class, () -> authorService.updateAuthor(id, author));

    verify(cache, times(1)).remove(author.getName().hashCode());
    verify(authorRepository, times(1)).save(existingAuthor);
  }
}
