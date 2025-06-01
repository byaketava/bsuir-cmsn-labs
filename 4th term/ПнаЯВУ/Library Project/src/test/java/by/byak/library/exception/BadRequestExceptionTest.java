package by.byak.library.exception;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;

class BadRequestExceptionTest {

  @Test
  void testConstructor() {
    BadRequestException exception = new BadRequestException("Bad request");

    assertEquals("Bad request", exception.getMessage());
  }
}
