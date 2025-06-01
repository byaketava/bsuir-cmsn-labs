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
import jakarta.transaction.Transactional;
import java.util.List;
import lombok.AllArgsConstructor;
import org.springframework.stereotype.Service;

@Service
@AllArgsConstructor
@Transactional
public class AuthorService {
  private final AuthorRepository authorRepository;
  private final AuthorDtoMapper authorMapper;
  private final InMemoryCache<Integer, Author> cache;

  public List<AuthorDto> findAllAuthors() {
    return authorRepository.findAll().stream().map(authorMapper).toList();
  }

  public AuthorDto findByName(String name) {
    Author cachedAuthor = cache.get(name.hashCode());
    if (cachedAuthor != null) {
      return authorMapper.apply(cachedAuthor);
    }

    Author author = authorRepository.findByName(name)
        .orElseThrow(() -> new NotFoundException(
            "The author with that name has not been found"));
    cache.put(name.hashCode(), author);

    return authorMapper.apply(author);
  }

  public void addAuthor(Author author) {
    if (authorRepository.existsByName(author.getName())) {
      throw new AlreadyExistsException(
          "The author with that name already exists");
    }

    try {
      authorRepository.save(author);
    } catch (Exception e) {
      throw new InternalError("Internal server error occurred while adding author", e);
    }
  }

  public void deleteAuthorById(Long id) {
    Author author = authorRepository.findById(id)
        .orElseThrow(() -> new NotFoundException(
            "The author with that id has not been found"));
    authorRepository.delete(author);
    cache.remove(author.getName().hashCode());
  }

  public void updateAuthor(Long id, Author author) {
    Author existingAuthor = authorRepository.findById(id)
        .orElseThrow(() -> new NotFoundException(
            "The author with that id has not been found"));
    cache.remove(author.getName().hashCode());

    existingAuthor.setName(author.getName());
    existingAuthor.setBooks(author.getBooks());

    for (Book book : author.getBooks()) {
      book.setAuthor(existingAuthor);
    }

    try {
      authorRepository.save(existingAuthor);
    } catch (Exception e) {
      throw new BadRequestException(e.getMessage());
    }
  }
}
