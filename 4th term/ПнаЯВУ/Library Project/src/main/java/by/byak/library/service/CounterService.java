package by.byak.library.service;

import java.util.concurrent.atomic.AtomicInteger;
import org.springframework.stereotype.Service;

@Service
public class CounterService {
  private final AtomicInteger counter = new AtomicInteger(0);

  public synchronized void increment() {
    counter.incrementAndGet();
  }

  public synchronized int get() {
    return counter.get();
  }
}
