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
  
  class test_suite
  {
  public:
    test_suite(std::string name);

    void add_test(test_function const& test);
  
    void add_test(
      std::string const& name,
      std::function<void()> test);
  
    void operator()(std::ostream& os = std::cout);
  
  private:
    std::vector<test_function> m_tests;
    std::string const m_name;
  };

  namespace assert
  {
    void that(bool condition);
    void that(bool condition, std::string const& message);
  }
}
