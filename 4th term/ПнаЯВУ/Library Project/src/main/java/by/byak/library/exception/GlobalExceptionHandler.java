package by.byak.library.exception;

import java.util.Date;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.ControllerAdvice;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.context.request.WebRequest;
import org.springframework.web.servlet.mvc.method.annotation.ResponseEntityExceptionHandler;

@ControllerAdvice
public class GlobalExceptionHandler extends ResponseEntityExceptionHandler {
  @ExceptionHandler(Exception.class)
  public ResponseEntity<ExceptionDetails> handleAllExceptions(
      Exception e, WebRequest request) {
    ExceptionDetails details = new ExceptionDetails(new Date(),
        e.getMessage(), request.getDescription(false));
    return new ResponseEntity<>(details, HttpStatus.INTERNAL_SERVER_ERROR);
  }

  @ExceptionHandler(BadRequestException.class)
  public ResponseEntity<ExceptionDetails> invalidRequest(
      BadRequestException e, WebRequest request) {
    ExceptionDetails details = new ExceptionDetails(new Date(),
        e.getMessage(), request.getDescription(false));
    return new ResponseEntity<>(details, HttpStatus.BAD_REQUEST);
  }

  @ExceptionHandler(NotFoundException.class)
  public ResponseEntity<ExceptionDetails> resourceNotFound(
      NotFoundException e, WebRequest request) {
    ExceptionDetails details = new ExceptionDetails(new Date(),
        e.getMessage(), request.getDescription(false));
    return new ResponseEntity<>(details, HttpStatus.NOT_FOUND);
  }

  @ExceptionHandler(AlreadyExistsException.class)
  public ResponseEntity<ExceptionDetails> resourceAlreadyExists(
      AlreadyExistsException e, WebRequest request) {
    ExceptionDetails details = new ExceptionDetails(new Date(),
        e.getMessage(), request.getDescription(false));
    return new ResponseEntity<>(details, HttpStatus.CONFLICT);
  }
}
