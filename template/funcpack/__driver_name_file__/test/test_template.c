#include "unity.h"
#include "unity_internals.h"

void test_fail(){
    TEST_FAIL_MESSAGE("No Tests implemented!");
}

void setUp(void) {}
void tearDown(void) {}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_fail);
  return UNITY_END();
}
