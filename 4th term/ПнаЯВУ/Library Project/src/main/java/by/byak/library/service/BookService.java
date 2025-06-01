package by.byak.library.service;

import by.byak.library.cache.InMemoryCache;
import by.byak.library.dto.book.BookDto;
import by.byak.library.entity.Author;
import by.byak.library.entity.Book;
import by.byak.library.exception.AlreadyExistsException;
import by.byak.library.exception.BadRequestException;
import by.byak.library.exception.NotFoundException;
import by.byak.library.mapper.book.BookDtoMapper;
import by.byak.library.repository.AuthorRepository;
import by.byak.library.repository.BookRepository;
import jakarta.transaction.Transactional;
import java.util.List;
import java.util.Optional;
import lombok.AllArgsConstructor;
import org.springframework.stereotype.Service;

@Service
@AllArgsConstructor
@Transactional
public class BookService {
  private final BookRepository bookRepository;
  private final AuthorRepository authorRepository;
  private final BookDtoMapper bookMapper;
  private final InMemoryCache<Integer, Book> cache;

  public List<BookDto> findAllBooks() {
    return bookRepository.findAll().stream().map(bookMapper).toList();
  }

  public BookDto findBookByTitle(String title) {
    Book cachedBook = cache.get(title.hashCode());
    if (cachedBook != null) {
      return bookMapper.apply(cachedBook);
    }

    Book book = bookRepository.findByTitle(title)
        .orElseThrow(() -> new NotFoundException(
            "The book with that title has not been found"));
    cache.put(title.hashCode(), book);

    return bookMapper.apply(book);
  }

  public List<BookDto> findByAuthorIdAndGenreId(Long authorId, Long genreId) {
    List<Book> books = bookRepository
        .findByAuthorIdAndGenreId(authorId, genreId)
        .orElseThrow(() -> new NotFoundException(
            "Books were not found for the given author and genre"));
    return books.stream().map(bookMapper).toList();
  }

  public void addBook(Book book) {
    if (bookRepository.existsByTitle(book.getTitle())) {
      throw new AlreadyExistsException(
          "The book with that title already exists");
    }

    try {
      bookRepository.save(book);
    } catch (Exception e) {
      throw new BadRequestException("Exception occurred while saving book");
    }
  }

  public void addBooks(Long id, List<Book> books) {
    Optional<Author> optionalAuthor = authorRepository.findById(id);
    if (optionalAuthor.isEmpty()) {
      throw new NotFoundException("The author with that ID does not exist");
    }

    Author author = optionalAuthor.get();

    for (Book book : books) {
      if (bookRepository.existsByTitle(book.getTitle())) {
        throw new AlreadyExistsException(
            "The book with that title already exists");
      }
      book.setAuthor(author);
    }

    try {
      bookRepository.saveAll(books);
    } catch (Exception e) {
      throw new BadRequestException("Exception occurred while saving books");
    }
  }

  public void deleteBookById(Long id) {
    Book book = bookRepository.findById(id)
        .orElseThrow(() -> new NotFoundException(
            "The book with that id has not been found"));
    bookRepository.delete(book);
    cache.remove(book.getTitle().hashCode());
  }

  public void updateBook(Long id, Book book) {
    Book existingBook = bookRepository.findById(id)
        .orElseThrow(() -> new NotFoundException(
            "The book with that id has not been found"));
    cache.remove(book.getTitle().hashCode());

    existingBook.setTitle(book.getTitle());
    existingBook.setAuthor(book.getAuthor());
    existingBook.setGenres(book.getGenres());

    try {
      bookRepository.save(existingBook);
    } catch (Exception e) {
      throw new BadRequestException(e.getMessage());
    }
  }
}
