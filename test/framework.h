#include <exception>
#include <vector>
#include <functional>
#include <string>
#include <iostream>

namespace test
{
  class TestFunction
  {
  public:
    TestFunction(
      std::string const& name,
      std::function<void()> func)
      : m_name(name)
      , m_func(func)
      , m_ran(false)
      , m_passed(false)
      , m_error_string()
    { }
  
    void operator()()
    {
      m_ran = true;
      try
      {
        m_func();
      }
      catch (std::exception e)
      {
        m_error_string = e.what();
        m_passed = false;
        return;
      }
      m_passed = true;
    }

    std::string const& name() const
    {
      return m_name;
    }
  
    bool ran() const
    {
      return m_ran;
    }
  
    bool passed() const
    {
      return m_passed;
    }
  
  private:
    std::string const m_name;
    std::function<void()> const m_func;
  
    bool m_ran;
    bool m_passed;
    std::string m_error_string;
  };

  std::ostream& operator<<(
    std::ostream& os,
    TestFunction const& tf)
  {
    os << tf.name() << "\t"
       << "ran: " << tf.ran() << "\t"
       << "passed: " << tf.passed();
    return os;
  }
  
  class TestSuite
  {
  public:
    void add_test(TestFunction const& test)
    {
      m_tests.push_back(test);
    }
  
    void add_test(
      std::string const& name,
      std::function<void()> test)
    {
      m_tests.emplace_back(name, test);
    }
  
    void operator()()
    {
      for (auto test : m_tests)
      {
      }
    }
  
  private:
    std::vector<TestFunction> m_tests;
  };
}
