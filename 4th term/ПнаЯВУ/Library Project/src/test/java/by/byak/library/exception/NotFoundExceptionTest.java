package by.byak.library.exception;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;

class NotFoundExceptionTest {

  @Test
  void testConstructor() {
    NotFoundException exception = new NotFoundException("Test message");

    assertEquals("Test message", exception.getMessage());
  }
}