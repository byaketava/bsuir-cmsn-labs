package by.byak.library.repository;

import by.byak.library.entity.Book;
import java.util.List;
import java.util.Optional;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;
import org.springframework.stereotype.Repository;

@Repository
public interface BookRepository extends JpaRepository<Book, Long> {
  Optional<Book> findByTitle(String title);

  boolean existsByTitle(String title);

  @Query("SELECT b FROM Book b JOIN b.genres g JOIN b.author a "
      + "WHERE a.id = :authorId AND g.id = :genreId")
  Optional<List<Book>> findByAuthorIdAndGenreId(
      @Param("authorId") Long authorId,
      @Param("genreId") Long genreId);
}
