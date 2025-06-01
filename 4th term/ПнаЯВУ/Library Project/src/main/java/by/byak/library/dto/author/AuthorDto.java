package by.byak.library.dto.author;

import by.byak.library.dto.book.BookTitleDto;
import java.util.List;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class AuthorDto {
  private Long id;
  private String name;
  private List<BookTitleDto> books;
}
