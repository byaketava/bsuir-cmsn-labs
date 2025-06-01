package by.byak.library.controller;

import static jakarta.servlet.RequestDispatcher.ERROR_MESSAGE;

import by.byak.library.dto.author.AuthorDto;
import by.byak.library.dto.book.BookDto;
import by.byak.library.dto.genre.GenreDto;
import by.byak.library.entity.Book;
import by.byak.library.repository.BookRepository;
import by.byak.library.service.AuthorService;
import by.byak.library.service.BookService;
import by.byak.library.service.GenreService;
import jakarta.validation.Valid;
import java.util.List;
import java.util.Optional;
import lombok.AllArgsConstructor;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.servlet.mvc.support.RedirectAttributes;

@Controller
@RequestMapping("/api")
@AllArgsConstructor
public class BookController {
  private final BookService service;
  private final AuthorService authorService;
  private final GenreService genreService;
  private final BookRepository repository;
  private static final String SUCCESS = "Completed successfully";
  private static final String REDIRECT = "redirect:/api/books";

  @GetMapping
  public String homePage() {
    return "home";
  }

  @GetMapping("/info")
  public String info() {
    return "info";
  }

  @GetMapping("/contacts")
  public String contacts() {
    return "contacts";
  }

  @GetMapping("/books/findByAuthorAndGenre")
  public ResponseEntity<List<BookDto>> findByAuthorIdAndGenreId(@RequestParam Long authorId,
                                                                @RequestParam Long genreId) {
    List<BookDto> books = service.findByAuthorIdAndGenreId(authorId, genreId);
    return ResponseEntity.ok(books);
  }

  @GetMapping("/books")
  public String findAllBooks(Model model) {
    List<BookDto> books = service.findAllBooks();
    model.addAttribute("books", books);
    return "books";
  }

  @GetMapping("/books/find")
  public ResponseEntity<BookDto> findBookByTitle(@RequestParam String title) {
    BookDto book = service.findBookByTitle(title);
    return ResponseEntity.ok(book);
  }

  @GetMapping("/books/add")
  public String addBook(@ModelAttribute("book") final Book book, Model model) {
    List<AuthorDto> authors = authorService.findAllAuthors();
    List<GenreDto> genres = genreService.findAllGenres();

    model.addAttribute("authors", authors);
    model.addAttribute("genres", genres);

    return "addBook";
  }

  @PostMapping("/books/add")
  public String addBook(@Valid @ModelAttribute("book") final Book book,
                        final BindingResult bindingResult,
                        final RedirectAttributes redirectAttributes) {
    if (bindingResult.hasErrors()) {
      bindingResult.getAllErrors().forEach(
          error -> redirectAttributes.addFlashAttribute(ERROR_MESSAGE, error.getDefaultMessage()));
      return "addBook";
    }
    service.addBook(book);
    return REDIRECT;
  }

  @PostMapping("/books/addAuthorBooks")
  public ResponseEntity<String> addBooks(@RequestParam Long id, @RequestBody List<Book> books) {
    service.addBooks(id, books);
    return new ResponseEntity<>(SUCCESS, HttpStatus.CREATED);
  }

  @PostMapping("/books/delete/{id}")
  public String deleteBookById(@PathVariable Long id) {
    service.deleteBookById(id);
    return REDIRECT;
  }

  @GetMapping("/books/update/{id}")
  public String showUpdateForm(@PathVariable Long id, Model model) {
    Optional<Book> bookOptional = repository.findById(id);
    if (bookOptional.isPresent()) {
      Book book = bookOptional.get();
      List<AuthorDto> authors = authorService.findAllAuthors();
      List<GenreDto> genres = genreService.findAllGenres();
      model.addAttribute("book", book);
      model.addAttribute("authors", authors);
      model.addAttribute("genres", genres);
    }
    return "updateBook";
  }

  @PostMapping("/books/update/{id}")
  public String updateBook(@PathVariable Long id, @Valid @ModelAttribute("book") Book book,
                           BindingResult bindingResult, RedirectAttributes redirectAttributes) {
    if (bindingResult.hasErrors()) {
      bindingResult.getAllErrors().forEach(
          error -> redirectAttributes.addFlashAttribute(ERROR_MESSAGE, error.getDefaultMessage()));
      return "updateBook";
    }
    service.updateBook(id, book);
    return REDIRECT;
  }
}