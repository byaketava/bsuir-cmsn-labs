package by.byak.library.exception;

import org.junit.jupiter.api.Test;

import java.util.Date;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

class ExceptionDetailsTest {
  @Test
  void testGettersAndSetters() {
    Date timestamp = new Date();
    String message = "Test exception";
    String details = "Exception details";

    ExceptionDetails exceptionDetails = new ExceptionDetails();
    exceptionDetails.setTimestamp(timestamp);
    exceptionDetails.setMessage(message);
    exceptionDetails.setDetails(details);

    assertEquals(timestamp, exceptionDetails.getTimestamp());
    assertEquals(message, exceptionDetails.getMessage());
    assertEquals(details, exceptionDetails.getDetails());
  }

  @Test
  void testEqualsAndHashCode() {
    Date timestamp = new Date();
    ExceptionDetails exceptionDetails1 = new ExceptionDetails(timestamp, "Test exception", "Exception details");
    ExceptionDetails exceptionDetails2 = new ExceptionDetails(timestamp, "Test exception", "Exception details");

    assertEquals(exceptionDetails1, exceptionDetails2);
    assertEquals(exceptionDetails1.hashCode(), exceptionDetails2.hashCode());
  }

  @Test
  void testToString() {
    Date timestamp = new Date();
    ExceptionDetails exceptionDetails = new ExceptionDetails(timestamp, "Test exception", "Exception details");

    String toString = exceptionDetails.toString();

    assertNotNull(toString);
    assertTrue(toString.contains("ExceptionDetails"));
    assertTrue(toString.contains("timestamp=" + timestamp));
    assertTrue(toString.contains("message=Test exception"));
    assertTrue(toString.contains("details=Exception details"));
  }

  @Test
  void testNoArgsConstructor() {
    ExceptionDetails exceptionDetails = new ExceptionDetails();

    assertNotNull(exceptionDetails);
    assertNull(exceptionDetails.getTimestamp());
    assertNull(exceptionDetails.getMessage());
    assertNull(exceptionDetails.getDetails());
  }

  @Test
  void testAllArgsConstructor() {
    Date timestamp = new Date();
    String message = "Test exception";
    String details = "Exception details";

    ExceptionDetails exceptionDetails = new ExceptionDetails(timestamp, message, details);

    assertNotNull(exceptionDetails);
    assertEquals(timestamp, exceptionDetails.getTimestamp());
    assertEquals(message, exceptionDetails.getMessage());
    assertEquals(details, exceptionDetails.getDetails());
  }
}
