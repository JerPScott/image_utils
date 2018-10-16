#pragma once

#include <memory>
#include <array>

#include <cassert>

using pixel = std::array<unsigned char, 3>;

namespace pixel_utils
{
  inline unsigned char const& get_r(pixel const& p) { return p.at(0); }
  inline unsigned char const& get_g(pixel const& p) { return p.at(1); }
  inline unsigned char const& get_b(pixel const& p) { return p.at(2); }
  
  inline unsigned char& at_r(pixel& p) { return p.at(0); }
  inline unsigned char& at_g(pixel& p) { return p.at(1); }
  inline unsigned char& at_b(pixel& p) { return p.at(2); }
}

// h rows of w pixels
template<unsigned int w, unsigned int h>
class image_bytes
{
public:
  using ptr = std::shared_ptr<image_bytes<w, h>>;
  using const_ptr = std::shared_ptr<const image_bytes<w, h>>;

  static const unsigned int width = w;
  static const unsigned int height = h;

  image_bytes()
  { }

  image_bytes(pixel const& fill)
  {
    set(fill);
  }

  inline pixel const& get(unsigned int x, unsigned int y) const
  {
    return m_data[y][x];
  }

  inline pixel& at(unsigned int x, unsigned int y)
  {
    return m_data[y][x];
  }

  void set(pixel const& fill)
  {
    for (auto& row : m_data)
    {
      for (auto& pix : row)
      {
        pix = fill;
      }
    }
  }

  template<unsigned int image_width, unsigned int image_height>
  void set(
    unsigned int x_start,
    unsigned int y_start,
    image_bytes<image_width, image_height> const& image)
  {
    assert((x_start + image_width) <= width);
    assert((y_start + image_height) <= height);
    
    for (unsigned int x = 0; x < image_width; ++x)
    {
      for (unsigned int y = 0; y < image_height; ++y)
      {
        auto curr_x = x + x_start;
        auto curr_y = y + y_start;

        at(curr_x, curr_y) = image.get(x, y);
      }
    }
  }

  inline unsigned char get_r(unsigned int x, unsigned int y) const
  {
    return pixel_utils::get_r(m_data[y][x]);
  }
  inline unsigned char get_g(unsigned int x, unsigned int y) const
  {
    return pixel_utils::get_g(m_data[y][x]);
  }
  inline unsigned char get_b(unsigned int x, unsigned int y) const
  {
    return pixel_utils::get_b(m_data[y][x]);
  }

  inline unsigned char& at_r(unsigned int x, unsigned int y)
  {
    return pixel_utils::at_r(m_data[y][x]);
  }
  inline unsigned char& at_g(unsigned int x, unsigned int y)
  {
    return pixel_utils::at_g(m_data[y][x]);
  }
  inline unsigned char& at_b(unsigned int x, unsigned int y)
  {
    return pixel_utils::at_b(m_data[y][x]);
  }

private:
  std::array<std::array<pixel, w>, h> m_data;
};

