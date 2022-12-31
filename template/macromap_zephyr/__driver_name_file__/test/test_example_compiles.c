#include "unity.h"
#include "unity_internals.h"

#include "example_generic.c"

void test_example_compiles() {
  // Example code included above. If we run we have compiled :)
}

void setUp(void) {}
void tearDown(void) {}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_example_compiles);
  return UNITY_END();
}

