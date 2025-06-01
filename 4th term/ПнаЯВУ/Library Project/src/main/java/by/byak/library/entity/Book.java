package by.byak.library.entity;

import jakarta.persistence.*;
import java.util.ArrayList;
import java.util.List;
import lombok.Data;

@Data
@Entity
@Table(name = "book")
public class Book {
  @Id
  @GeneratedValue(strategy = GenerationType.IDENTITY)
  private Long id;

  @Column(name = "title", unique = true)
  private String title;

  @ManyToMany(cascade = {CascadeType.MERGE})
  @JoinTable(name = "book_genre",
      joinColumns = @JoinColumn(name = "book_id"),
      inverseJoinColumns = @JoinColumn(name = "genre_id"))

  private List<Genre> genres = new ArrayList<>();

  @ManyToOne
  @JoinColumn(name = "author_id")
  private Author author;
}
