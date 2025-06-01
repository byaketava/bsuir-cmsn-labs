package by.byak.library.controller;

import static jakarta.servlet.RequestDispatcher.ERROR_MESSAGE;

import by.byak.library.dto.genre.GenreDto;
import by.byak.library.entity.Genre;
import by.byak.library.repository.GenreRepository;
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
@RequestMapping("/api/genres")
@AllArgsConstructor
public class GenreController {
  private final GenreService service;
  private final BookService bookService;
  private final GenreRepository repository;
  private static final String SUCCESS = "Completed successfully";
  private static final String REDIRECT = "redirect:/api/genres";

  @GetMapping
  public String findAllGenres(Model model) {
    List<GenreDto> genres = service.findAllGenres();
    model.addAttribute("genres", genres);
    model.addAttribute("books", bookService.findAllBooks());
    return "genres";
  }

  @GetMapping("/find")
  public ResponseEntity<GenreDto> findGenreByName(@RequestParam String name) {
    GenreDto genre = service.findGenreByName(name);
    return ResponseEntity.ok(genre);
  }

  @GetMapping("/add")
  public String addGenre(@ModelAttribute("genre") Genre genre) {
    return "addGenre";
  }

  @PostMapping("/add")
  public String addGenre(@Valid @ModelAttribute("genre") Genre genre,
                         final BindingResult bindingResult,
                         final RedirectAttributes redirectAttributes) {
    if (bindingResult.hasErrors()) {
      bindingResult.getAllErrors().forEach(
          error -> redirectAttributes.addFlashAttribute(ERROR_MESSAGE, error.getDefaultMessage()));
      return "addGenre";
    }
    service.addGenre(genre);
    return REDIRECT;
  }

  @PostMapping("/addBasic")
  public ResponseEntity<String> addGenreBasic(@RequestBody Genre genre) {
    service.addGenre(genre);
    return new ResponseEntity<>(SUCCESS, HttpStatus.CREATED);
  }

  @PostMapping("/delete/{id}")
  public String deleteGenreById(@PathVariable Long id) {
    service.deleteGenreById(id);
    return REDIRECT;
  }

  @GetMapping("/update/{id}")
  public String showUpdateForm(@PathVariable Long id, Model model) {
    Optional<Genre> genreOptional = repository.findById(id);
    if (genreOptional.isPresent()) {
      Genre genre = genreOptional.get();
      model.addAttribute("genre", genre);
    }
    return "updateGenre";
  }

  @PostMapping("/update/{id}")
  String updateGenre(@PathVariable Long id, @Valid @ModelAttribute("genre") Genre genre,
                     BindingResult bindingResult, RedirectAttributes redirectAttributes) {
    if (bindingResult.hasErrors()) {
      bindingResult.getAllErrors().forEach(
          error -> redirectAttributes.addFlashAttribute(ERROR_MESSAGE, error.getDefaultMessage()));
      return "updateGenre";
    }
    service.updateGenre(id, genre);
    return REDIRECT;
  }
}
