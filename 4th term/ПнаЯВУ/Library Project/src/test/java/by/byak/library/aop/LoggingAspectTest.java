package by.byak.library.aop;

import ch.qos.logback.classic.Logger;
import ch.qos.logback.classic.spi.ILoggingEvent;
import ch.qos.logback.core.read.ListAppender;
import org.aspectj.lang.ProceedingJoinPoint;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.slf4j.LoggerFactory;

import java.util.List;

import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.when;

class LoggingAspectTest {

  private ListAppender<ILoggingEvent> listAppender;

  @BeforeEach
  void setUp() {
    Logger logger = (Logger) LoggerFactory.getLogger(LoggingAspect.class);

    listAppender = new ListAppender<>();
    listAppender.start();

    logger.addAppender(listAppender);
  }

  @Test
  void testLogExecutionTime() throws Throwable {
    ProceedingJoinPoint joinPoint = mock(ProceedingJoinPoint.class);
    when(joinPoint.proceed()).thenReturn("testResult");

    LoggingAspect loggingAspect = new LoggingAspect();
    loggingAspect.logExecutionTime(joinPoint);

    List<ILoggingEvent> logsList = listAppender.list;
    assertTrue(
        logsList.stream().anyMatch(event -> event.getFormattedMessage().contains("executed in")));
  }
}