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
  
  ///// test_suite /////
  test_suite::test_suite(std::string name)
    : m_name(name) { }

  void test_suite::add_test(test_function const& test)
  {
    m_tests.push_back(test);
  }
  
  void test_suite::add_test(
    std::string const& name,
    std::function<void()> test)
  {
    m_tests.emplace_back(name, test);
  }
  
  void test_suite::operator()(std::ostream& os /*= std::cout*/)
  {
    os << "Running Test Suite: "
       << m_name
       << std::endl;

    for (auto test : m_tests)
    {
      test();
      os << test;
      os << std::endl;
    }
  }
  ///// test_suite /////

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
