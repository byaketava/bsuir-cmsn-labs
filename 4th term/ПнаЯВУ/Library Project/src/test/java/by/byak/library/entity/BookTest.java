package by.byak.library.entity;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

import java.util.ArrayList;
import java.util.List;

class BookTest {

  private Book book;
  private Author author;

  @BeforeEach
  void setup() {
    book = new Book();
    book.setId(1L);
    book.setTitle("Test Book");

    author = new Author();
    author.setId(1L);
    author.setName("Test Author");

    book.setAuthor(author);
  }

  @Test
  void testGetId() {
    assertEquals(1L, book.getId());
  }

  @Test
  void testSetId() {
    book.setId(2L);
    assertEquals(2L, book.getId());
  }

  @Test
  void testGetTitle() {
    assertEquals("Test Book", book.getTitle());
  }

  @Test
  void testSetTitle() {
    book.setTitle("New Title");
    assertEquals("New Title", book.getTitle());
  }

  @Test
  void testGetAuthor() {
    assertEquals(author, book.getAuthor());
  }

  @Test
  void testSetAuthor() {
    Author newAuthor = new Author();
    newAuthor.setId(2L);
    newAuthor.setName("New Author");

    book.setAuthor(newAuthor);
    assertEquals(newAuthor, book.getAuthor());
  }

  @Test
  void testGetGenres() {
    assertNotNull(book.getGenres());
    assertTrue(book.getGenres().isEmpty());
  }

  @Test
  void testSetGenres() {
    Genre genre1 = new Genre();
    genre1.setId(1L);
    genre1.setName("Genre 1");

    Genre genre2 = new Genre();
    genre2.setId(2L);
    genre2.setName("Genre 2");

    List<Genre> genres = new ArrayList<>();
    genres.add(genre1);
    genres.add(genre2);

    book.setGenres(genres);

    assertEquals(2, book.getGenres().size());
    assertTrue(book.getGenres().contains(genre1));
    assertTrue(book.getGenres().contains(genre2));
  }

  @Test
  void testEqualsAndHashCode() {
    Book book1 = new Book();
    book1.setTitle("Test Title");

    Book book2 = new Book();
    book2.setTitle("Test Title");

    assertEquals(book1, book2);
    assertEquals(book1.hashCode(), book2.hashCode());
  }

  @Test
  void testToString() {
    Book book = new Book();
    book.setTitle("Test Title");

    assertTrue(book.toString().contains("Test Title"));
  }
}
