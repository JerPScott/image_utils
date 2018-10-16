#include "unit/image_bytes_suite.h"
#include "unit/bitmap_suite.h"

int main()
{
  int result = 0;

  image_bytes_suite _image_bytes_suite;
  if (!_image_bytes_suite()) result = -1;

  bitmap_suite _bitmap_suite;
  if (!_bitmap_suite()) result = -1;

  return result;
}
