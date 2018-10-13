#include "../framework.h"

struct image_bytes_suite
  : public test::Itest_suite
{
  image_bytes_suite()
    : m_image_bytes_group("image bytes group")
  {
  }

  bool operator()() override
  {
    return m_image_bytes_group();
  }

  ~image_bytes_suite() { }

  test::test_group m_image_bytes_group;
};
