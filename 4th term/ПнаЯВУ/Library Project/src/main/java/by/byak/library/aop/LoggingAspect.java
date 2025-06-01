package by.byak.library.aop;

import org.aspectj.lang.JoinPoint;
import org.aspectj.lang.ProceedingJoinPoint;
import org.aspectj.lang.annotation.*;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.stereotype.Component;

@Aspect
@Component
public class LoggingAspect {
  private static final Logger LOGGER = LoggerFactory.getLogger(
      LoggingAspect.class);

  @Pointcut("execution(public * by.byak.library.service.*.*(..))")
  public void logServiceMethods() {
  }

  @AfterThrowing(pointcut = "logServiceMethods()", throwing = "exception")
  public void logException(JoinPoint joinPoint, Throwable exception) throws Throwable {
    String methodName = joinPoint.getSignature().getName();
    LOGGER.error("Exception thrown in method: {} with message: {}",
        methodName, exception.getMessage());
    throw exception;
  }

  @Before("logServiceMethods()")
  public void logMethodCall(JoinPoint joinPoint) {
    String methodName = joinPoint.getSignature().getName();
    LOGGER.info("Method called: {}", methodName);
  }

  @Around("logServiceMethods()")
  public Object logExecutionTime(
      ProceedingJoinPoint joinPoint) throws Throwable {
    long start = System.currentTimeMillis();
    Object proceed = joinPoint.proceed();
    long executionTime = System.currentTimeMillis() - start;
    LOGGER.info("{} executed in {}ms",
        joinPoint.getSignature(), executionTime);
    return proceed;
  }

  @AfterReturning(pointcut = "logServiceMethods()", returning = "result")
  public void logMethodReturn(JoinPoint joinPoint, Object result) {
    String methodName = joinPoint.getSignature().getName();
    LOGGER.info("Method return: {} returned {}", methodName, result);
  }
}
