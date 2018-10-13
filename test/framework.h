#pragma once

#include <exception>
#include <vector>
#include <functional>
#include <string>
#include <iostream>

namespace test
{
  class test_exception : public std::exception
  {
  public:
    test_exception(std::string const& what = std::string());

    char const* what() const noexcept override;

  private:
    std::string m_what;
  };

  class test_function
  {
  public:
    test_function(
      std::string const& name,
      std::function<void()> func);
  
    void operator()();

    std::string const& name() const;
    std::string const& error() const;
    bool ran() const;
    bool passed() const;

  private:
    std::string const m_name;
    std::function<void()> const m_func;
  
    bool m_ran;
    bool m_passed;
    std::string m_error_string;
  };

  std::ostream& operator<<(
    std::ostream& os,
    test_function const& tf);
  
  class test_group
  {
  public:
    test_group(
      std::string name,
      std::function<void()> group_setup = std::function<void()>(),
      std::function<void()> group_teardown = std::function<void()>(),
      std::function<void()> test_setup = std::function<void()>(),
      std::function<void()> test_teardown = std::function<void()>());

    void add_test(test_function const& test);
  
    void add_test(
      std::string const& name,
      std::function<void()> test);
  
    bool operator()(std::ostream& os = std::cout);
  
  private:
    std::vector<test_function> m_tests;
    std::string const m_name;

    bool m_all_passed;

    // before test group
    std::function<void()> const m_group_setup;
    // after test group
    std::function<void()> const m_group_teardown;
    // before each test
    std::function<void()> const m_test_setup;
    // after each test
    std::function<void()> const m_test_teardown;
  };

  class Itest_suite
  {
  protected:
    virtual bool operator()() = 0;
    virtual ~Itest_suite() { }
  };

  namespace assert
  {
    void that(bool condition);
    void that(bool condition, std::string const& message);
  }
}
