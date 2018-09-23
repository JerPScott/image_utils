#include "bitmap.h"

int main()
{
  const unsigned int k_width = 1040;
  const unsigned int k_height = 700;
  //const pixel k_black_pixel = { 0, 0, 0 };
  const pixel k_white_pixel = { 255, 255, 255 };
  const pixel k_r_pixel = { 255, 0, 0 };
  const pixel k_g_pixel = { 0, 255, 0 };
  const pixel k_b_pixel = { 0, 0, 255 };

  auto test_image = std::make_shared<image_bytes<k_width, k_height>>();

  auto active_color = k_r_pixel;
  auto passive_color = k_g_pixel;
  for (unsigned int x = 0; x < k_width; x++)
  {
    for (unsigned int y = 0; y < k_height; y++)
    {
      if ((x%50<25) == (y%50<25))
      {
        test_image->at(x, y) = active_color;
      }
      else
      {
        test_image->at(x, y) = passive_color;
      }
    }
    if (x == k_width/2)
    {
      active_color = k_white_pixel;
      passive_color = k_b_pixel;
    }
  }

  auto test_bmp = bitmap<k_width, k_height>::create_shared(test_image);

  test_bmp->save("test_output");
}
