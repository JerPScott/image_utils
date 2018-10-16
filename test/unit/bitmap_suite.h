#include "bitmap.h"
#include "image_bytes.h"
#include "../framework.h"

void create_shared_test()
{
  // arrange
  const pixel blank_pixel = { 0, 0, 0 };
  const pixel set_pixel = { 1, 1, 1 };

  auto p_test_bytes = std::make_shared<image_bytes<2, 2>>(blank_pixel);

  // act
  auto p_test_bmp_one = bitmap<2, 2>::create_shared(p_test_bytes);

  p_test_bytes->at(0, 0) = set_pixel;

  // assert
  test::assert::that(p_test_bmp_one->m_image->get(0, 0) == set_pixel);
}

void create_copy_test()
{
  // arrange
  const pixel blank_pixel = { 0, 0, 0 };
  const pixel set_pixel = { 1, 1, 1 };

  auto p_test_bytes = std::make_shared<image_bytes<2, 2>>(blank_pixel);

  // act
  auto p_test_bmp_one = bitmap<2, 2>::create_copy(p_test_bytes);

  p_test_bytes->at(0, 0) = set_pixel;

  // assert
  test::assert::that(p_test_bmp_one->m_image->get(0, 0) == blank_pixel);
}

struct bitmap_suite
  : public test::Itest_suite
{
  bitmap_suite()
    : m_create_group("create group")
  {
    m_create_group.add_test("create_shared_test", create_shared_test);
    m_create_group.add_test("create_copy_test", create_copy_test);
  }

  bool operator()() override
  {
    return m_create_group();
  }

  ~bitmap_suite() { }

private:
  test::test_group m_create_group;
};
