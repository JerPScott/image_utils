#include "image_bytes.h"
#include "../framework.h"

void basic_construction_test()
{
  // arrange
  const int test_width = 1;
  const int test_height = 3;

  // act
  image_bytes<test_width, test_height> test_bytes;

  // assert
  test::assert::that(test_bytes.width == test_width);
  test::assert::that(test_bytes.height == test_height);
}

void red_test()
{
  // arrange
  const unsigned char red_value = 5;
  const unsigned char blank_value = 0;
  const pixel blank_pixel = { blank_value, blank_value, blank_value };

  image_bytes<1, 1> test_bytes;
  test_bytes.at(0, 0) = blank_pixel;

  // act
  test_bytes.at_r(0, 0) = red_value;

  // assert
  test::assert::that(test_bytes.at_r(0, 0) == red_value);
  test::assert::that(test_bytes.at_g(0, 0) == blank_value);
  test::assert::that(test_bytes.at_b(0, 0) == blank_value);
}

void green_test()
{
  // arrange
  const unsigned char green_value = 5;
  const unsigned char blank_value = 0;
  const pixel blank_pixel = { blank_value, blank_value, blank_value };

  image_bytes<1, 1> test_bytes;
  test_bytes.at(0, 0) = blank_pixel;

  // act
  test_bytes.at_g(0, 0) = green_value;

  // assert
  test::assert::that(test_bytes.at_r(0, 0) == blank_value);
  test::assert::that(test_bytes.at_g(0, 0) == green_value);
  test::assert::that(test_bytes.at_b(0, 0) == blank_value);
}

void blue_test()
{
  // arrange
  const unsigned char blue_value = 5;
  const unsigned char blank_value = 0;
  const pixel blank_pixel = { blank_value, blank_value, blank_value };

  image_bytes<1, 1> test_bytes;
  test_bytes.at(0, 0) = blank_pixel;

  // act
  test_bytes.at_b(0, 0) = blue_value;

  // assert
  test::assert::that(test_bytes.at_r(0, 0) == blank_value);
  test::assert::that(test_bytes.at_g(0, 0) == blank_value);
  test::assert::that(test_bytes.at_b(0, 0) == blue_value);
}

struct image_bytes_suite
  : public test::Itest_suite
{
  image_bytes_suite()
    : m_image_bytes_group("image bytes group")
  {
    m_image_bytes_group.add_test("basic_construction_test", basic_construction_test);
    m_image_bytes_group.add_test("red_test", red_test);
    m_image_bytes_group.add_test("green_test", green_test);
    m_image_bytes_group.add_test("blue_test", blue_test);
  }

  bool operator()() override
  {
    return m_image_bytes_group();
  }

  ~image_bytes_suite() { }

  test::test_group m_image_bytes_group;
};
