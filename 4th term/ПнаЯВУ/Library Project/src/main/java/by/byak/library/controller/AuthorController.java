package by.byak.library.controller;

import static jakarta.servlet.RequestDispatcher.ERROR_MESSAGE;

import by.byak.library.dto.author.AuthorDto;
import by.byak.library.entity.Author;
import by.byak.library.repository.AuthorRepository;
import by.byak.library.service.AuthorService;
import by.byak.library.service.BookService;
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
@RequestMapping("/api/authors")
@AllArgsConstructor
public class AuthorController {
  private final AuthorService service;
  private final BookService bookService;
  private final AuthorRepository repository;
  private static final String SUCCESS = "Completed successfully";
  private static final String REDIRECT = "redirect:/api/authors";

  @GetMapping
  public String findAllAuthors(Model model) {
    List<AuthorDto> authors = service.findAllAuthors();
    model.addAttribute("authors", authors);
    model.addAttribute("books", bookService.findAllBooks());
    return "authors";
  }

  @GetMapping("/find")
  public ResponseEntity<AuthorDto> findByName(@RequestParam String name) {
    AuthorDto author = service.findByName(name);
    return ResponseEntity.ok(author);
  }

  @GetMapping("/add")
  public String addAuthor(@ModelAttribute("author") Author author) {
    return "addAuthor";
  }

  @PostMapping("/add")
  public String addAuthor(@Valid @ModelAttribute("author") Author author,
                          final BindingResult bindingResult,
                          final RedirectAttributes redirectAttributes) {
    if (bindingResult.hasErrors()) {
      bindingResult.getAllErrors().forEach(
          error -> redirectAttributes.addFlashAttribute(ERROR_MESSAGE, error.getDefaultMessage()));
      return "addAuthor";
    }
    service.addAuthor(author);
    return REDIRECT;
  }

  @PostMapping("/addBasic")
  public ResponseEntity<String> addAuthorBasic(@RequestBody Author author) {
    service.addAuthor(author);
    return new ResponseEntity<>(SUCCESS, HttpStatus.CREATED);
  }

  @PostMapping("/delete/{id}")
  public String deleteAuthorById(@PathVariable Long id) {
    service.deleteAuthorById(id);
    return REDIRECT;
  }

  @GetMapping("/update/{id}")
  public String showUpdateForm(@PathVariable Long id, Model model) {
    Optional<Author> authorOptional = repository.findById(id);
    if (authorOptional.isPresent()) {
      Author author = authorOptional.get();
      model.addAttribute("author", author);
    }
    return "updateAuthor";
  }

  @PostMapping("/update/{id}")
  String updateAuthor(@PathVariable Long id, @Valid @ModelAttribute("author") Author author,
                      BindingResult bindingResult, RedirectAttributes redirectAttributes) {
    if (bindingResult.hasErrors()) {
      bindingResult.getAllErrors().forEach(
          error -> redirectAttributes.addFlashAttribute(ERROR_MESSAGE, error.getDefaultMessage()));
      return "updateAuthor";
    }
    service.updateAuthor(id, author);
    return REDIRECT;
  }
}
