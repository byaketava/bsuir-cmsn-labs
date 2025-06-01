package by.byak.library.cache;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class InMemoryCacheTest {

  private InMemoryCache<String, Integer> cache;

  @BeforeEach
  void setup() {
    cache = new InMemoryCache<>();
  }

  @Test
  void testGet() {
    cache.put("key", 1);

    Integer value = cache.get("key");

    assertEquals(1, value);
  }

  @Test
  void testPut() {
    cache.put("key", 1);

    Integer value = cache.get("key");

    assertEquals(1, value);
  }

  @Test
  void testRemove() {
    cache.put("key", 1);

    cache.remove("key");

    assertNull(cache.get("key"));
  }

  @Test
  void testClear() {
    cache.put("key1", 1);
    cache.put("key2", 2);

    cache.clear();

    assertNull(cache.get("key1"));
    assertNull(cache.get("key2"));
  }
}
