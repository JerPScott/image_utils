#include "framework.h"

namespace test
{
  ///// test_exception /////
  test_exception::test_exception(std::string const& what)
    : m_what(what) { }

  char const* test_exception::what() const noexcept
  {
    return m_what.c_str();
  }
  ///// test_exception /////

  ///// test_function /////
  test_function::test_function(
    std::string const& name,
    std::function<void()> func)
    : m_name(name)
    , m_func(func)
    , m_ran(false)
    , m_passed(false)
    , m_error_string()
  { }
  
  void test_function::operator()()
  {
    m_ran = true;
    try
    {
      m_func();
    }
    catch (test_exception const& e)
    {
      m_error_string = e.what();
      m_passed = false;
      return;
    }
    m_passed = true;
  }

  std::string const& test_function::name() const
  {
    return m_name;
  }
  
  bool test_function::ran() const
  {
    return m_ran;
  }
  
  bool test_function::passed() const
  {
    return m_passed;
  }

  std::string const& test_function::error() const
  {
    return m_error_string;
  }
  ///// test_function /////

  std::ostream& operator<<(
    std::ostream& os,
    test_function const& tf)
  {
    os << tf.name()
       << "\t" << "ran: " << tf.ran()
       << "\t" << "passed: " << tf.passed();

    if (!tf.passed())
    {
      os << "\t" << "error: " << tf.error();
    }

    return os;
  }
  
  ///// test_group /////
  test_group::test_group(
    std::string name,
    std::function<void()> group_setup /*= std::function<void()>()*/,
    std::function<void()> group_teardown /*= std::function<void()>()*/,
    std::function<void()> test_setup /*= std::function<void()>()*/,
    std::function<void()> test_teardown /*= std::function<void()>()*/)
    : m_name(name)
    , m_all_passed(true)
    , m_group_setup(group_setup)
    , m_group_teardown(group_teardown)
    , m_test_setup(test_setup)
    , m_test_teardown(test_teardown)
  { }

  void test_group::add_test(test_function const& test)
  {
    m_tests.push_back(test);
  }
  
  void test_group::add_test(
    std::string const& name,
    std::function<void()> test)
  {
    m_tests.emplace_back(name, test);
  }
  
  bool test_group::operator()(std::ostream& os /*= std::cout*/)
  {
    os << "Running Test Group: "
       << m_name
       << std::endl;

    if (m_group_setup) m_group_setup();
    for (auto test : m_tests)
    {
      if (m_test_setup) m_test_setup();
      test();
      if (m_test_teardown) m_test_teardown();
      os << test;
      os << std::endl;
      m_all_passed &= test.passed();
    }
    if (m_group_teardown) m_group_teardown();
    return m_all_passed;
  }
  ///// test_group /////

  namespace assert
  {
    void that(bool condition)
    {
      if (!condition) throw test_exception();
    }

    void that(bool condition, std::string const& message)
    {
      if (!condition) throw test_exception(message);
    }
  }
}
