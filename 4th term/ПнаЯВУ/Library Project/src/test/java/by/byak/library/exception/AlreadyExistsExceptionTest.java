package by.byak.library.exception;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;

class AlreadyExistsExceptionTest {

  @Test
  void testConstructor() {
    AlreadyExistsException exception = new AlreadyExistsException("Item already exists");

    assertEquals("Item already exists", exception.getMessage());
  }
}
