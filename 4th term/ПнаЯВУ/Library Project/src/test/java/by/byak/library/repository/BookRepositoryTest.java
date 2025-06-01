package by.byak.library.repository;

import by.byak.library.entity.Book;
import by.byak.library.entity.Author;
import by.byak.library.entity.Genre;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

import static org.mockito.Mockito.*;

class BookRepositoryTest {

  @Mock
  private BookRepository bookRepository;

  @BeforeEach
  void setup() {
    MockitoAnnotations.openMocks(this);
  }

  @Test
  void testFindByTitle() {
    // Arrange
    String title = "The Great Gatsby";
    Book book = new Book();
    book.setTitle(title);
    when(bookRepository.findByTitle(title)).thenReturn(Optional.of(book));

    Optional<Book> result = bookRepository.findByTitle(title);

    Assertions.assertTrue(result.isPresent());
    Assertions.assertEquals(book, result.get());

    verify(bookRepository, times(1)).findByTitle(title);
  }

  @Test
  void testExistsByTitle() {
    String title = "The Great Gatsby";
    when(bookRepository.existsByTitle(title)).thenReturn(true);

    boolean result = bookRepository.existsByTitle(title);

    Assertions.assertTrue(result);

    verify(bookRepository, times(1)).existsByTitle(title);
  }

  @Test
  void testFindByAuthorIdAndGenreId() {
    Long authorId = 1L;
    Long genreId = 2L;

    Author author = new Author();
    author.setId(authorId);
    author.setName("F. Scott Fitzgerald");

    Genre genre = new Genre();
    genre.setId(genreId);
    genre.setName("Fiction");

    Book book1 = new Book();
    book1.setId(1L);
    book1.setTitle("The Great Gatsby");
    book1.setAuthor(author);

    Book book2 = new Book();
    book2.setId(2L);
    book2.setTitle("Tender Is the Night");
    book2.setAuthor(author);

    List<Book> books = new ArrayList<>();
    books.add(book1);
    books.add(book2);

    when(bookRepository.findByAuthorIdAndGenreId(authorId, genreId)).thenReturn(Optional.of(books));

    Optional<List<Book>> result = bookRepository.findByAuthorIdAndGenreId(authorId, genreId);

    Assertions.assertTrue(result.isPresent());
    Assertions.assertEquals(books, result.get());

    verify(bookRepository, times(1)).findByAuthorIdAndGenreId(authorId, genreId);
  }
}
