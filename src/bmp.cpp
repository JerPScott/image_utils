#include "bitmap.h"

int main()
{
  const unsigned int k_width = 1040;
  const unsigned int k_height = 700;
  const pixel k_blank_pixel = { 0, 0, 0 };
  const pixel k_r_pixel = { 255, 0, 0 };
  const pixel k_g_pixel = { 0, 255, 0 };
  const pixel k_b_pixel = { 0, 0, 255 };

  auto test_image = std::make_shared<image_bytes<k_width, k_height>>();

  for (unsigned int x = 0; x < k_width; x++)
  {
    for (unsigned int y = 0; y < k_height/4; y++)
    {
      test_image->at(x, y) = k_r_pixel;
    }
    for (unsigned int y = k_height/4; y < k_height*2/4; y++)
    {
      test_image->at(x, y) = k_g_pixel;
    }
    for (unsigned int y = k_height*2/4; y < k_height*3/4; y++)
    {
      test_image->at(x, y) = k_b_pixel;
    }
    for (unsigned int y = k_height*3/4; y < k_height; y++)
    {
      test_image->at(x, y) = k_blank_pixel;
    }
  }

  auto test_bmp = bitmap<k_width, k_height>::create_shared(test_image);

  test_bmp->save("test_output");
}
