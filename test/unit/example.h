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
  : public test::Itest_suite
{
  example()
    : m_example_group("example group")
  {
    m_example_group.add_test("example_fail", example_fail);
    m_example_group.add_test("example_pass", example_pass);
  }

  void operator()() override
  {
    m_example_group();
  }

  ~example() { }

  test::test_group m_example_group;
};
