package by.byak.library.service;

import by.byak.library.cache.InMemoryCache;
import by.byak.library.dto.genre.GenreDto;
import by.byak.library.entity.Book;
import by.byak.library.entity.Genre;
import by.byak.library.exception.AlreadyExistsException;
import by.byak.library.exception.BadRequestException;
import by.byak.library.exception.NotFoundException;
import by.byak.library.mapper.genre.GenreDtoMapper;
import by.byak.library.repository.BookRepository;
import by.byak.library.repository.GenreRepository;
import jakarta.transaction.Transactional;
import java.util.List;
import lombok.AllArgsConstructor;
import org.springframework.stereotype.Service;

@Service
@AllArgsConstructor
@Transactional
public class GenreService {
  private final GenreRepository genreRepository;
  private final BookRepository bookRepository;
  private final GenreDtoMapper genreMapper;
  private final InMemoryCache<Integer, Genre> cache;
  private final InMemoryCache<Integer, Book> bookCache;

  public List<GenreDto> findAllGenres() {
    return genreRepository.findAll().stream().map(genreMapper).toList();
  }

  public GenreDto findGenreByName(String name) {
    Genre cachedGenre = cache.get(name.hashCode());
    if (cachedGenre != null) {
      return genreMapper.apply(cachedGenre);
    }

    Genre genre = genreRepository.findByName(name)
        .orElseThrow(() -> new NotFoundException(
            "The genre with that name has not been found"));
    cache.put(name.hashCode(), genre);

    return genreMapper.apply(genre);
  }

  public void addGenre(Genre genre) {
    if (genreRepository.existsByName(genre.getName())) {
      throw new AlreadyExistsException(
          "The genre with that name already exists");
    }

    try {
      genreRepository.save(genre);
    } catch (Exception e) {
      throw new BadRequestException(e.getMessage());
    }
  }

  public void deleteGenreById(Long id) {
    Genre genre = genreRepository.findById(id)
        .orElseThrow(() -> new NotFoundException(
            "The genre with that id has not been found"));

    for (Book book : genre.getBooks()) {
      book.getGenres().remove(genre);
      try {
        bookRepository.save(book);
      } catch (Exception e) {
        throw new BadRequestException(e.getMessage());
      }
      bookCache.remove(book.getTitle().hashCode());
    }

    genreRepository.delete(genre);
    cache.remove(genre.getName().hashCode());
  }

  public void updateGenre(Long id, Genre genre) {
    Genre existingGenre = genreRepository.findById(id)
        .orElseThrow(() -> new NotFoundException(
            "The genre with that id has not been found"));
    cache.remove(genre.getName().hashCode());

    existingGenre.setName(genre.getName());
    existingGenre.setBooks(genre.getBooks());

    try {
      genreRepository.save(existingGenre);
    } catch (Exception e) {
      throw new BadRequestException(e.getMessage());
    }
  }
}
