/*
package by.byak.library.controller;

import by.byak.library.dto.book.BookDto;
import by.byak.library.entity.Book;
import by.byak.library.service.AuthorService;
import by.byak.library.service.BookService;
import java.util.Arrays;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;

import java.util.ArrayList;
import java.util.List;
import org.springframework.ui.Model;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.mockito.Mockito.*;

class BookControllerTest {

  private BookController bookController;

  @Mock
  private BookService bookService;
  private AuthorService authorService;

  @BeforeEach
  public void setup() {
    MockitoAnnotations.openMocks(this);
    bookController = new BookController(bookService, authorService);
  }

  @Test
  void testFindByAuthorIdAndGenreId() {
    Long authorId = 1L;
    Long genreId = 2L;

    List<BookDto> books = new ArrayList<>();
    when(bookService.findByAuthorIdAndGenreId(authorId, genreId)).thenReturn(books);

    ResponseEntity<List<BookDto>> response =
        bookController.findByAuthorIdAndGenreId(authorId, genreId);

    verify(bookService, times(1)).findByAuthorIdAndGenreId(authorId, genreId);
    assertEquals(HttpStatus.OK, response.getStatusCode());
    assertEquals(books, response.getBody());
  }

  @Test
  void testFindAllBooks() {
    List<BookDto> books = new ArrayList<>();
    when(bookService.findAllBooks()).thenReturn(books);

    String expectedViewName = "books";
    Model model = mock(Model.class);

    String resultViewName = bookController.findAllBooks(model);

    verify(bookService, times(1)).findAllBooks();
    assertEquals(expectedViewName, resultViewName);
    verify(model, times(1)).addAttribute("books", books);
  }

  @Test
  void testFindBookByTitle() {
    String title = "Test Book";

    BookDto bookDto = new BookDto();
    when(bookService.findBookByTitle(title)).thenReturn(bookDto);

    ResponseEntity<BookDto> response = bookController.findBookByTitle(title);

    verify(bookService, times(1)).findBookByTitle(title);
    assertEquals(HttpStatus.OK, response.getStatusCode());
    assertEquals(bookDto, response.getBody());
  }

  @Test
  void testAddBook() {
    Book book = new Book();

    ResponseEntity<String> response = bookController.addBook(book);

    verify(bookService, times(1)).addBook(book);
    assertEquals(HttpStatus.CREATED, response.getStatusCode());
    assertEquals("Completed successfully", response.getBody());
  }

  @Test
  void testAddBooks() {
    Long id = 1L;
    List<Book> books = Arrays.asList(new Book(), new Book());

    ResponseEntity<String> response = bookController.addBooks(id, books);

    verify(bookService, times(1)).addBooks(id, books);
    assertEquals(HttpStatus.CREATED, response.getStatusCode());
    assertEquals("Completed successfully", response.getBody());
  }

  @Test
  void testDeleteBookById() {
    Long id = 1L;

    ResponseEntity<String> response = bookController.deleteBookById(id);

    verify(bookService, times(1)).deleteBookById(id);
    assertEquals(HttpStatus.OK, response.getStatusCode());
    assertEquals("Completed successfully", response.getBody());
  }

  @Test
  void testUpdateBook() {
    Long id = 1L;
    Book book = new Book();

    ResponseEntity<String> response = bookController.updateBook(id, book);

    verify(bookService, times(1)).updateBook(id, book);
    assertEquals(HttpStatus.OK, response.getStatusCode());
    assertEquals("Completed successfully", response.getBody());
  }
}
*/
