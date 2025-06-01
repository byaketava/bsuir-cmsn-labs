/*
package by.byak.library.controller;

import by.byak.library.dto.author.AuthorDto;
import by.byak.library.entity.Author;
import by.byak.library.service.AuthorService;
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

class AuthorControllerTest {

  private AuthorController authorController;

  @Mock
  private AuthorService authorService;

  @BeforeEach
  public void setup() {
    MockitoAnnotations.openMocks(this);
    authorController = new AuthorController(authorService);
  }

  @Test
  void testFindAllAuthors() {
    List<AuthorDto> authorDtos = new ArrayList<>();
    when(authorService.findAllAuthors()).thenReturn(authorDtos);

    ResponseEntity<List<AuthorDto>> response = authorController.findAllAuthors();

    verify(authorService, times(1)).findAllAuthors();
    assertEquals(HttpStatus.OK, response.getStatusCode());
    assertEquals(authorDtos, response.getBody());
  }

  @Test
  void testFindByName() {
    String name = "Test Author";

    AuthorDto authorDto = new AuthorDto();
    when(authorService.findByName(name)).thenReturn(authorDto);

    ResponseEntity<AuthorDto> response = authorController.findByName(name);

    verify(authorService, times(1)).findByName(name);
    assertEquals(HttpStatus.OK, response.getStatusCode());
    assertEquals(authorDto, response.getBody());
  }

  @Test
  void testAddAuthor() {
    Author author = new Author();

    ResponseEntity<String> response = authorController.addAuthor(author);

    verify(authorService, times(1)).addAuthor(author);
    assertEquals(HttpStatus.CREATED, response.getStatusCode());
    assertEquals("Completed successfully", response.getBody());
  }

  @Test
  void testDeleteAuthorById() {
    Long id = 1L;

    ResponseEntity<String> response = authorController.deleteAuthorById(id);

    verify(authorService, times(1)).deleteAuthorById(id);
    assertEquals(HttpStatus.OK, response.getStatusCode());
    assertEquals("Completed successfully", response.getBody());
  }

  @Test
  void testUpdateAuthor() {
    Long id = 1L;
    Author author = new Author();

    ResponseEntity<String> response = authorController.updateAuthor(id, author);

    verify(authorService, times(1)).updateAuthor(id, author);
    assertEquals(HttpStatus.OK, response.getStatusCode());
    assertEquals("Completed successfully", response.getBody());
  }
}
*/
