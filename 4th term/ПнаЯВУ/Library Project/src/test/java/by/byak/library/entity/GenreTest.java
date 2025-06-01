package by.byak.library.entity;

import java.util.ArrayList;
import java.util.List;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class GenreTest {

  private Genre genre;
  private Book book1;
  private Book book2;

  @BeforeEach
  public void setup() {
    genre = new Genre();
    genre.setId(1L);
    genre.setName("Test Genre");

    book1 = new Book();
    book1.setId(1L);
    book1.setTitle("Book 1");

    book2 = new Book();
    book2.setId(2L);
    book2.setTitle("Book 2");

    List<Book> books = new ArrayList<>();
    books.add(book1);
    books.add(book2);

    genre.setBooks(books);
  }

  @Test
  void testGetId() {
    assertEquals(1L, genre.getId());
  }

  @Test
  void testSetId() {
    genre.setId(2L);
    assertEquals(2L, genre.getId());
  }

  @Test
  void testGetName() {
    assertEquals("Test Genre", genre.getName());
  }

  @Test
  void testSetName() {
    genre.setName("New Genre");
    assertEquals("New Genre", genre.getName());
  }

  @Test
  void testGetBooks() {
    assertEquals(2, genre.getBooks().size());
    assertTrue(genre.getBooks().contains(book1));
    assertTrue(genre.getBooks().contains(book2));
  }

  @Test
  void testSetBooks() {
    Book newBook = new Book();
    newBook.setId(3L);
    newBook.setTitle("Book 3");

    List<Book> books = new ArrayList<>();
    books.add(newBook);

    genre.setBooks(books);

    assertEquals(1, genre.getBooks().size());
    assertTrue(genre.getBooks().contains(newBook));
  }

  @Test
  void testEqualsAndHashCode() {
    Genre genre1 = new Genre();
    genre1.setName("Test Genre");

    Genre genre2 = new Genre();
    genre2.setName("Test Genre");

    assertEquals(genre1, genre2);
    assertEquals(genre1.hashCode(), genre2.hashCode());
  }

  @Test
  void testToString() {
    Genre genre = new Genre();
    genre.setName("Test Genre");

    assertTrue(genre.toString().contains("Test Genre"));
  }
}
