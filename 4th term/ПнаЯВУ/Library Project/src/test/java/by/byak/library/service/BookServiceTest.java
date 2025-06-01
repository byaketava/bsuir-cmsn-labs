package by.byak.library.service;

import by.byak.library.cache.InMemoryCache;
import by.byak.library.dto.book.BookDto;
import by.byak.library.entity.Author;
import by.byak.library.entity.Book;
import by.byak.library.entity.Genre;
import by.byak.library.exception.AlreadyExistsException;
import by.byak.library.exception.BadRequestException;
import by.byak.library.exception.NotFoundException;
import by.byak.library.mapper.book.BookDtoMapper;
import by.byak.library.repository.AuthorRepository;
import by.byak.library.repository.BookRepository;
import java.util.Collections;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.Mockito.*;

@SuppressWarnings("MismatchedQueryAndUpdateOfCollection")
class BookServiceTest {
  @Mock
  private AuthorRepository authorRepository;

  @Mock
  private BookRepository bookRepository;

  @Mock
  private BookDtoMapper bookMapper;

  @Mock
  private InMemoryCache<Integer, Book> cache;

  @InjectMocks
  private BookService bookService;

  @BeforeEach
  public void setup() {
    MockitoAnnotations.openMocks(this);
  }

  @Test
  void testFindAllBooks() {
    List<Book> books = new ArrayList<>();
    books.add(new Book());
    books.add(new Book());

    when(bookRepository.findAll()).thenReturn(books);

    List<BookDto> bookDtos = new ArrayList<>();
    bookDtos.add(new BookDto());
    bookDtos.add(new BookDto());

    when(bookMapper.apply(any(Book.class))).thenReturn(new BookDto());

    List<BookDto> result = bookService.findAllBooks();

    assertEquals(2, result.size());
    verify(bookRepository, times(1)).findAll();
    verify(bookMapper, times(2)).apply(any(Book.class));
    verify(bookMapper, times(books.size())).apply(any(Book.class));
  }

  @Test
  void testFindBookByTitle_BookFoundInCache() {
    String title = "Test Book";
    Book cachedBook = new Book();
    cachedBook.setTitle(title);

    when(cache.get(title.hashCode())).thenReturn(cachedBook);

    BookDto bookDto = new BookDto();
    bookDto.setTitle(title);

    when(bookMapper.apply(cachedBook)).thenReturn(bookDto);

    BookDto result = bookService.findBookByTitle(title);

    assertEquals(title, result.getTitle());
    verify(cache, times(1)).get(title.hashCode());
    verify(bookMapper, times(1)).apply(cachedBook);
    verify(bookRepository, never()).findByTitle(title);
  }

  @Test
  void testFindBookByTitle_BookNotFoundInCache() {
    String title = "Test Book";
    Book book = new Book();
    BookDto bookDto = new BookDto();

    when(cache.get(title.hashCode())).thenReturn(null);
    when(bookRepository.findByTitle(title)).thenReturn(Optional.of(book));
    when(bookMapper.apply(book)).thenReturn(bookDto);

    BookDto result = bookService.findBookByTitle(title);

    assertEquals(bookDto, result);
    verify(cache, times(1)).get(title.hashCode());
    verify(bookRepository, times(1)).findByTitle(title);
    verify(bookMapper, times(1)).apply(book);
  }

  @Test
  void testFindBookByTitle_BookNotFoundInRepository() {
    String title = "The Great Gatsby";
    when(bookRepository.findByTitle(title)).thenReturn(Optional.empty());

    Assertions.assertThrows(NotFoundException.class, () -> bookService.findBookByTitle(title));

    verify(bookRepository, times(1)).findByTitle(title);
    Assertions.assertNull(cache.get(title.hashCode()));
  }

  @Test
  void testFindByAuthorIdAndGenreId_BooksFound() {
    Long authorId = 1L;
    Long genreId = 2L;

    List<Book> books = new ArrayList<>();
    books.add(new Book());
    books.add(new Book());

    when(bookRepository.findByAuthorIdAndGenreId(authorId, genreId)).thenReturn(Optional.of(books));

    List<BookDto> bookDtos = new ArrayList<>();
    bookDtos.add(new BookDto());
    bookDtos.add(new BookDto());

    when(bookMapper.apply(any(Book.class))).thenReturn(new BookDto());

    List<BookDto> result = bookService.findByAuthorIdAndGenreId(authorId, genreId);

    assertEquals(2, result.size());
    verify(bookRepository, times(1)).findByAuthorIdAndGenreId(authorId, genreId);
    verify(bookMapper, times(2)).apply(any(Book.class));
  }

  @Test
  void testFindByAuthorIdAndGenreId_BooksNotFound() {
    Long authorId = 1L;
    Long genreId = 2L;

    when(bookRepository.findByAuthorIdAndGenreId(authorId, genreId)).thenReturn(Optional.empty());

    assertThrows(NotFoundException.class,
        () -> bookService.findByAuthorIdAndGenreId(authorId, genreId));

    verify(bookRepository, times(1)).findByAuthorIdAndGenreId(authorId, genreId);
    verify(bookMapper, never()).apply(any(Book.class));
  }

  @Test
  void testAddBook_BookDoesNotExist() {
    Book book = new Book();
    book.setTitle("New Book");

    when(bookRepository.existsByTitle(book.getTitle())).thenReturn(false);

    bookService.addBook(book);

    verify(bookRepository, times(1)).existsByTitle(book.getTitle());
    verify(bookRepository, times(1)).save(book);
  }

  @Test
  void testAddBook_BookAlreadyExists() {
    Book book = new Book();
    book.setTitle("ExistingBook");

    when(bookRepository.existsByTitle(book.getTitle())).thenReturn(true);

    assertThrows(AlreadyExistsException.class, () -> bookService.addBook(book));

    verify(bookRepository, times(1)).existsByTitle(book.getTitle());
    verify(bookRepository, never()).save(book);
  }

  @Test
  void testAddBook_ExceptionWhileSavingBook() {
    Book book = new Book();
    book.setTitle("New Book");

    when(bookRepository.existsByTitle(book.getTitle())).thenReturn(false);
    doThrow(BadRequestException.class).when(bookRepository).save(book);

    assertThrows(BadRequestException.class, () -> bookService.addBook(book));

    verify(bookRepository, times(1)).existsByTitle(book.getTitle());
    verify(bookRepository, times(1)).save(book);
  }

  @Test
  void testAddBooksWithExistingAuthor() {
    Author author = new Author();
    author.setId(1L);
    author.setName("John Doe");

    List<Book> books = new ArrayList<>();
    Book book1 = new Book();
    book1.setTitle("Book 1");
    Book book2 = new Book();
    book2.setTitle("Book 2");
    books.add(book1);
    books.add(book2);

    when(authorRepository.findById(1L)).thenReturn(Optional.of(author));
    when(bookRepository.existsByTitle(anyString())).thenReturn(false);

    bookService.addBooks(1L, books);

    verify(bookRepository, times(1)).saveAll(books);
    verify(authorRepository, times(1)).findById(1L);
    verify(bookRepository, times(2)).existsByTitle(anyString());
  }

  @Test
  void testAddBooksWithNonExistentAuthor() {
    when(authorRepository.findById(1L)).thenReturn(Optional.empty());

    assertThrows(NotFoundException.class, () -> bookService.addBooks(1L, new ArrayList<>()));

    verify(authorRepository, times(1)).findById(1L);
    verify(bookRepository, never()).existsByTitle(anyString());
    verify(bookRepository, never()).saveAll(anyList());
  }

  @Test
  void testAddBooksWithBookThatAlreadyExists() {
    Author author = new Author();
    author.setId(1L);
    author.setName("John Doe");

    List<Book> books = new ArrayList<>();
    Book book1 = new Book();
    book1.setTitle("Book 1");
    Book book2 = new Book();
    book2.setTitle("Book 2");
    books.add(book1);
    books.add(book2);

    when(authorRepository.findById(1L)).thenReturn(Optional.of(author));
    when(bookRepository.existsByTitle("Book 1")).thenReturn(true);

    assertThrows(AlreadyExistsException.class, () -> bookService.addBooks(1L, books));

    verify(authorRepository, times(1)).findById(1L);
    verify(bookRepository, times(1)).existsByTitle("Book 1");
    verify(bookRepository, never()).saveAll(anyList());
  }

  @Test
  void testAddBooksWithException() {
    Author author = new Author();
    author.setId(1L);
    author.setName("John Doe");

    List<Book> books = new ArrayList<>();
    Book book1 = new Book();
    book1.setTitle("Book 1");
    Book book2 = new Book();
    book2.setTitle("Book 2");
    books.add(book1);
    books.add(book2);

    when(authorRepository.findById(1L)).thenReturn(Optional.of(author));
    when(bookRepository.existsByTitle(anyString())).thenReturn(false);
    when(bookRepository.saveAll(anyList())).thenThrow(new RuntimeException("Exception occurred"));

    assertThrows(BadRequestException.class, () -> bookService.addBooks(1L, books));

    verify(authorRepository, times(1)).findById(1L);
    verify(bookRepository, times(2)).existsByTitle(anyString());
    verify(bookRepository, times(1)).saveAll(anyList());
  }

  @Test
  void testDeleteBookById_BookExists() {
    Long id = 1L;
    String title = "Test Book";
    Book book = new Book();
    book.setId(id);
    book.setTitle(title);

    when(bookRepository.findById(id)).thenReturn(Optional.of(book));

    bookService.deleteBookById(id);

    verify(bookRepository, times(1)).findById(id);
    verify(bookRepository, times(1)).delete(book);
    verify(cache, times(1)).remove(title.hashCode());
  }

  @Test
  void testDeleteBookById_BookNotFound() {
    Long id = 1L;

    when(bookRepository.findById(id)).thenReturn(Optional.empty());

    assertThrows(NotFoundException.class, () -> bookService.deleteBookById(id));

    verify(bookRepository, times(1)).findById(id);
    verify(bookRepository, never()).delete(any(Book.class));
    verify(cache, never()).remove(anyInt());
  }

  @Test
  void testUpdateBook_ExceptionDuringSave() {
    Long id = 1L;
    Book book = new Book();
    book.setTitle("Updated Title");

    Book existingBook = new Book();
    existingBook.setTitle("Old Title");

    when(bookRepository.findById(id)).thenReturn(Optional.of(existingBook));
    doThrow(new RuntimeException("Save failed")).when(bookRepository).save(existingBook);

    assertThrows(BadRequestException.class, () -> bookService.updateBook(id, book));

    verify(cache, times(1)).remove(book.getTitle().hashCode());
    verify(bookRepository, times(1)).save(existingBook);
  }

  @Test
  void testUpdateBook_BookNotFound() {
    Long id = 1L;
    Book book = new Book();

    when(bookRepository.findById(id)).thenReturn(Optional.empty());

    assertThrows(NotFoundException.class, () -> bookService.updateBook(id, book));

    verify(bookRepository, times(1)).findById(id);
    verify(cache, never()).remove(anyInt());
    verify(bookRepository, never()).save(any(Book.class));
  }

  @Test
  void testUpdateBook_BookExists() {
    Long id = 1L;
    List<Genre> genres = Collections.singletonList(new Genre());
    Author author = new Author();

    Book inputBook = new Book();
    inputBook.setTitle("Updated Title");
    inputBook.setAuthor(author);
    inputBook.setGenres(genres);

    Book existingBook = new Book();
    existingBook.setTitle("Old Title");
    existingBook.setAuthor(new Author());
    existingBook.setGenres(Collections.singletonList(new Genre()));

    when(bookRepository.findById(id)).thenReturn(Optional.of(existingBook));

    bookService.updateBook(id, inputBook);

    assertEquals(inputBook.getTitle(), existingBook.getTitle());
    assertEquals(inputBook.getAuthor(), existingBook.getAuthor());
    assertEquals(inputBook.getGenres(), existingBook.getGenres());
    verify(cache, times(1)).remove(inputBook.getTitle().hashCode());
    verify(bookRepository, times(1)).save(existingBook);
  }
}