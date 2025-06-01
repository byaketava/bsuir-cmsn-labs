package by.byak.library.repository;

import by.byak.library.entity.Genre;
import java.util.Optional;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface GenreRepository extends JpaRepository<Genre, Long> {
  Optional<Genre> findByName(String name);

  boolean existsByName(String name);
}
