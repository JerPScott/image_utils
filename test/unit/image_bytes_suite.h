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
  test::assert::that(
    test_bytes.width == test_width,
    "width incorrect");
  test::assert::that(
    test_bytes.height == test_height,
    "height incorrect");
}

void pixel_red_test()
{
  // arrange
  const unsigned int blank_value = 0;
  const unsigned int set_value = 1;
  pixel p = { blank_value, blank_value, blank_value };

  // act
  pixel_utils::at_r(p) = set_value;

  // assert
  test::assert::that(
    pixel_utils::get_r(p) == set_value,
    "red not set");
  test::assert::that(
    pixel_utils::get_g(p) == blank_value,
    "green erroneously set");
  test::assert::that(
    pixel_utils::get_b(p) == blank_value,
    "blue erroneously set");
}

void pixel_green_test()
{
  // arrange
  const unsigned int blank_value = 0;
  const unsigned int set_value = 1;
  pixel p = { blank_value, blank_value, blank_value };

  // act
  pixel_utils::at_g(p) = set_value;

  // assert
  test::assert::that(
    pixel_utils::get_r(p) == blank_value,
    "red set erroneously");
  test::assert::that(
    pixel_utils::get_g(p) == set_value,
    "green not set");
  test::assert::that(
    pixel_utils::get_b(p) == blank_value,
    "blue set erroneously");
}

void pixel_blue_test()
{
  // arrange
  const unsigned int blank_value = 0;
  const unsigned int set_value = 1;
  pixel p = { blank_value, blank_value, blank_value };

  // act
  pixel_utils::at_b(p) = set_value;

  // assert
  test::assert::that(
    pixel_utils::get_r(p) == blank_value,
    "red set erroneously");
  test::assert::that(
    pixel_utils::get_g(p) == blank_value,
    "green set erroneously");
  test::assert::that(
    pixel_utils::get_b(p) == set_value,
    "blue not set");
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
  test::assert::that(
    test_bytes.at_r(0, 0) == red_value,
    "red not set");
  test::assert::that(
    test_bytes.at_g(0, 0) == blank_value,
    "green set erroneously");
  test::assert::that(
    test_bytes.at_b(0, 0) == blank_value,
    "blue set errnoesouly");
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
  test::assert::that(
    test_bytes.at_r(0, 0) == blank_value,
    "red set errnoeously");
  test::assert::that(
    test_bytes.at_g(0, 0) == green_value,
    "green not set");
  test::assert::that(
    test_bytes.at_b(0, 0) == blank_value,
    "blue set erronesouly");
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
  test::assert::that(
    test_bytes.at_r(0, 0) == blank_value,
    "red set erroneously");
  test::assert::that(
    test_bytes.at_g(0, 0) == blank_value,
    "green set erroneously");
  test::assert::that(
    test_bytes.at_b(0, 0) == blue_value,
    "blue not set");
}

void fill_test()
{
  // arrange
  const pixel blank_pixel = { 0, 0, 0 };
  const pixel set_pixel = { 1, 1, 1 };

  const int test_width = 2;
  const int test_height = 3;

  image_bytes<test_width, test_height> test_bytes;

  // act
  test_bytes.set(blank_pixel);

  // assert
  for (int w = 0; w < test_width; w++)
  {
    for (int h = 0; h < test_height; h++)
    {
      test::assert::that(
        test_bytes.get(w, h) == blank_pixel,
        "image bytes not cleared. w: " + std::to_string(w) +
        ", h: " + std::to_string(h));
    }
  }

  // act
  test_bytes.set(set_pixel);

  // assert
  for (int w = 0; w < test_width; w++)
  {
    for (int h = 0; h < test_height; h++)
    {
      test::assert::that(
        test_bytes.get(w, h) == set_pixel,
        "image bytes not set. w: " + std::to_string(w) +
        ", h: " + std::to_string(h));
    }
  }
}

void fill_section_test()
{
  // arrange
  const pixel blank_pixel = { 0, 0, 0 };
  const pixel set_pixel = { 1, 1, 1 };

  const int width = 2;
  const int height = 3;

  const int sub_width = 1;
  const int sub_height = 2;

  image_bytes<width, height> test_bytes;
  image_bytes<sub_width, sub_height> sub_bytes;

  test_bytes.set(blank_pixel);
  sub_bytes.set(set_pixel);

  // act
  test_bytes.set(0, 0, sub_bytes);

  // assert
  for (int w = 0; w < width; w++)
  {
    for (int h = 0; h < height; h++)
    {
      if (w < sub_width && h < sub_height)
      {
        test::assert::that(
          test_bytes.get(w, h) == set_pixel,
          "pixel not set. w: " + std::to_string(w) +
          ", h: " + std::to_string(h));
      }
      else
      {
        test::assert::that(
          test_bytes.get(w, h) == blank_pixel,
          "pixel set erroneously. w: " + std::to_string(w) +
          ", h: " + std::to_string(h));
      }
    }
  }
}

struct image_bytes_suite
  : public test::Itest_suite
{
  image_bytes_suite()
    : m_pixel_group("pixel group")
    , m_image_bytes_group("image bytes group")
    , m_area_set_group("area set group")
  {
    m_pixel_group.add_test("pixel_red_test", pixel_red_test);
    m_pixel_group.add_test("pixel_green_test", pixel_green_test);
    m_pixel_group.add_test("pixel_blue_test", pixel_blue_test);

    m_image_bytes_group.add_test("basic_construction_test", basic_construction_test);
    m_image_bytes_group.add_test("red_test", red_test);
    m_image_bytes_group.add_test("green_test", green_test);
    m_image_bytes_group.add_test("blue_test", blue_test);

    m_area_set_group.add_test("fill_test", fill_test);
    m_area_set_group.add_test("fill_section_test", fill_section_test);
  }

  bool operator()() override
  {
    return
      m_pixel_group() &&
      m_image_bytes_group() &&
      m_area_set_group();
  }

  ~image_bytes_suite() { }

private:
  test::test_group m_pixel_group;
  test::test_group m_image_bytes_group;
  test::test_group m_area_set_group;
};
