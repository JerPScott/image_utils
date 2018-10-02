#include "../framework.h"

void example_fail()
{
  test::assert::that(false, "we auto failed this");
}

void example_pass()
{
  test::assert::that(true, "this should not fail");
}

struct example
{
  example()
    : m_example_suite("example suite")
  {
    m_example_suite.add_test("example_fail", example_fail);
    m_example_suite.add_test("example_pass", example_pass);
  }

  void operator()()
  {
    m_example_suite();
  }

  test::test_suite m_example_suite;
};
