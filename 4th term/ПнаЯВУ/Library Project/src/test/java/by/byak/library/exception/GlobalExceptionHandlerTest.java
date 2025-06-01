package by.byak.library.exception;

import org.junit.jupiter.api.Test;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.context.request.WebRequest;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.when;

class GlobalExceptionHandlerTest {

  @Test
  void testHandleAllExceptions() {
    GlobalExceptionHandler handler = new GlobalExceptionHandler();
    Exception exception = new Exception("Test exception");
    WebRequest request = mock(WebRequest.class);
    when(request.getDescription(false)).thenReturn("Test request description");

    ResponseEntity<ExceptionDetails> response = handler.handleAllExceptions(exception, request);

    assertNotNull(response);
    assertEquals(HttpStatus.INTERNAL_SERVER_ERROR, response.getStatusCode());
    ExceptionDetails details = response.getBody();
    assertNotNull(details);
    assertEquals(exception.getMessage(), details.getMessage());
    assertNotNull(details.getTimestamp());
  }

  @Test
  void testHandleBadRequestException() {
    GlobalExceptionHandler handler = new GlobalExceptionHandler();
    BadRequestException exception = new BadRequestException("Invalid request");
    WebRequest request = mock(WebRequest.class);
    when(request.getDescription(false)).thenReturn("Test request description");

    ResponseEntity<ExceptionDetails> response = handler.invalidRequest(exception, request);

    assertNotNull(response);
    assertEquals(HttpStatus.BAD_REQUEST, response.getStatusCode());
    ExceptionDetails details = response.getBody();
    assertNotNull(details);
    assertEquals(exception.getMessage(), details.getMessage());
    assertNotNull(details.getTimestamp());
  }

  @Test
  void testHandleNotFoundException() {
    GlobalExceptionHandler handler = new GlobalExceptionHandler();
    NotFoundException exception = new NotFoundException("Resource not found");
    WebRequest request = mock(WebRequest.class);
    when(request.getDescription(false)).thenReturn("Test request description");

    ResponseEntity<ExceptionDetails> response = handler.resourceNotFound(exception, request);

    assertNotNull(response);
    assertEquals(HttpStatus.NOT_FOUND, response.getStatusCode());
    ExceptionDetails details = response.getBody();
    assertNotNull(details);
    assertEquals(exception.getMessage(), details.getMessage());
    assertNotNull(details.getTimestamp());
  }

  @Test
  void testHandleAlreadyExistsException() {
    GlobalExceptionHandler handler = new GlobalExceptionHandler();
    AlreadyExistsException exception = new AlreadyExistsException("Resource already exists");
    WebRequest request = mock(WebRequest.class);
    when(request.getDescription(false)).thenReturn("Test request description");

    ResponseEntity<ExceptionDetails> response = handler.resourceAlreadyExists(exception, request);

    assertNotNull(response);
    assertEquals(HttpStatus.CONFLICT, response.getStatusCode());
    ExceptionDetails details = response.getBody();
    assertNotNull(details);
    assertEquals(exception.getMessage(), details.getMessage());
    assertNotNull(details.getTimestamp());
  }
}
