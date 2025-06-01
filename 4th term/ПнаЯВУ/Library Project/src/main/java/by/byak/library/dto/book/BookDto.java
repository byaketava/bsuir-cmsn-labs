package by.byak.library.dto.book;

import by.byak.library.dto.author.AuthorNameDto;
import by.byak.library.dto.genre.GenreNameDto;
import java.util.List;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class BookDto {
  private Long id;
  private String title;
  private List<GenreNameDto> genres;
  private AuthorNameDto author;
}
