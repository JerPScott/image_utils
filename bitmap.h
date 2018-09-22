#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <array>

#include "debug.h"

namespace detail
{
  const std::array<unsigned char, 14> k_BITMAPFILEHEADER_TEMPLATE =
  {
    'B', 'M',     // B, M to declare bitmap file.
    0, 0, 0, 0,   // Size of the file in bytes.
    0, 0,         // Reserved must be 0.
    0, 0,         // Reserved must be 0.
    54, 0, 0, 0   // Offset from beggining fo file to bitmap data.
  };
  
  const std::array<unsigned char, 40> k_BITMAPINFOHEADER_TEMPLATE =
  {
    40, 0, 0, 0,  // Size of BITMAPINFOHEADER in bytes.
    0, 0, 0, 0,   // Image width in pixels.
    0, 0, 0, 0,   // Image height in pixels.
    1, 0,         // Must be 0.
    32, 0,        // Number of bits per pixel.
    0, 0, 0, 0,   // Type of compression. (0 for none)
    0, 0, 0, 0,   // Size of image data in bytes. (0 when no compression)
    0, 0, 0, 0,   // Horozontal pixels per meter. (can be 0)
    0, 0, 0, 0,   // Virtical pixels per meter. (can be 0)
    0, 0, 0, 0,   // Number of colors. (0 => calculated from bits per pixel)
    0, 0, 0, 0    // Number of important colors. (0 => all colors)
  };
}

using pixel = std::array<unsigned char, 3>;

// y rows of w pixels
template<unsigned int w, unsigned int h>
struct image_bytes
{
  using ptr = std::shared_ptr<image_bytes<w, h>>;
  using const_ptr = std::shared_ptr<const image_bytes<w, h>>;

  inline pixel const& get(unsigned int x, unsigned int y)
  {
    return m_data[y][x];
  }

  inline pixel& at(unsigned int x, unsigned int y)
  {
    return m_data[y][x];
  }

  inline unsigned char get_r(unsigned int x, unsigned int y)
  {
    return m_data[y][x][0];
  }
  inline unsigned char get_g(unsigned int x, unsigned int y)
  {
    return m_data[y][x][1];
  }
  inline unsigned char get_b(unsigned int x, unsigned int y)
  {
    return m_data[y][x][2];
  }

  inline unsigned char& at_r(unsigned int x, unsigned int y)
  {
    return m_data[y][x][0];
  }
  inline unsigned char& at_g(unsigned int x, unsigned int y)
  {
    return m_data[y][x][1];
  }
  inline unsigned char& at_b(unsigned int x, unsigned int y)
  {
    return m_data[y][x][2];
  }

  std::array<std::array<pixel, w>, h> m_data;
};

// w => width in pixels of the image.
// h => height in pixels of the image.
template<unsigned int w, unsigned int h>
class bitmap
{
public:
  using ptr = std::shared_ptr<bitmap<w, h>>;

  static ptr create_shared(typename image_bytes<w, h>::ptr image)
  {
    return std::shared_ptr<bitmap<w, h>>(new bitmap<w, h>(image));
  }

  static ptr create_copy(typename image_bytes<w, h>::const_ptr image)
  {
    return std::shared_ptr<bitmap<w, h>>(new bitmap<w, h>(image));
  }

  bool save(std::string const& file_name)
  {
    const std::string full_file_name = file_name + ".bmp";
    std::ofstream o_file_stream;
    o_file_stream.open(full_file_name, std::ios::out | std::ios::binary);
    if (!o_file_stream.good())
    {
      std::cerr << "ERROR: bitmap<w, h>::save : ";
      std::cerr << "Unable to open the file for writing";
      std::cerr << std::endl;
      return false;
    }
  
    if (!write(o_file_stream))
    {
      std::cerr << "ERROR: bitmap<w, h>::save : ";
      std::cerr << "Write failed";
      std::cerr << std::endl;
      return false;
    }
  
    o_file_stream.flush();
    o_file_stream.close();
    if (!o_file_stream.good())
    {
      std::cerr << "ERROR: bitmap<w, h>::save : ";
      std::cerr << "Unable to close the file after writing";
      std::cerr << std::endl;
      return false;
    }
  
    return true;
  }

  bool write(std::ofstream& o_file_stream)
  {
    // write file header
    o_file_stream.write((char*)m_BITMAPFILEHEADER.data(), std::streamsize(14));
    if (!o_file_stream.good())
    {
      std::cerr << "ERROR: bitmap<w, h>::write : ";
      std::cerr << "Write fialed at file header : ";
      std::cerr << o_file_stream.rdstate();
      std::cerr << std::endl;
      std::cerr << "fail(): " << o_file_stream.fail() << std::endl;
      std::cerr << "bad(): " << o_file_stream.bad() << std::endl;

      print_last_error();
      return false;
    }
  
    // write bitmap info header
    o_file_stream.write((char*)m_BITMANINFOHEADER.data(), std::streamsize(40));
    if (!o_file_stream.good())
    {
      std::cerr << "ERROR: bitmap<w, h>::write : ";
      std::cerr << "Write fialed at bitmap info header";
      std::cerr << std::endl;

      print_last_error();
      return false;
    }
  
    // write image data
    // bitmaps are stored upside down
    for (auto it_row = m_image->m_data.crbegin(); it_row != m_image->m_data.crend(); ++it_row)
    {
      for (auto it_pixel = it_row->cbegin(); it_pixel != it_row->cend(); it_pixel++)
      {
        o_file_stream << (unsigned char)(*it_pixel)[2];
        o_file_stream << (unsigned char)(*it_pixel)[1];
        o_file_stream << (unsigned char)(*it_pixel)[0];
        o_file_stream << (unsigned char)(0); // padding byte
      }
    }
    if (!o_file_stream.good())
    {
      std::cerr << "ERROR: bitmap<w, h>::write : ";
      std::cerr << "Write fialed during image data";
      std::cerr << std::endl;

      print_last_error();
      return false;
    }
  
    return true;
  }

private:

  bitmap(typename image_bytes<w, h>::ptr image)
  {
    m_image = image;
    _setup_headers();
  }

  bitmap(typename image_bytes<w, h>::const_ptr image)
  {
    m_image = std::make_shared<image_bytes<w, h>>(*image);
    _setup_headers();
  }

  void _setup_headers()
  {
    static const unsigned int header_size_bytes = 54;
    static const unsigned int bytes_per_pixel = 4; // r, g, b, padding byte
    static const unsigned int pixel_count = w*h;
  
    unsigned int file_size_bytes = 
      header_size_bytes + bytes_per_pixel*pixel_count;

    m_BITMAPFILEHEADER = detail::k_BITMAPFILEHEADER_TEMPLATE;
    m_BITMANINFOHEADER = detail::k_BITMAPINFOHEADER_TEMPLATE;
  
    // file size
    m_BITMAPFILEHEADER[2] = (unsigned char)(file_size_bytes);
    m_BITMAPFILEHEADER[3] = (unsigned char)(file_size_bytes >> 8);
    m_BITMAPFILEHEADER[4] = (unsigned char)(file_size_bytes >> 16);
    m_BITMAPFILEHEADER[5] = (unsigned char)(file_size_bytes >> 24);
  
    // bitmap width
    m_BITMANINFOHEADER[4] = (unsigned char)(w);
    m_BITMANINFOHEADER[5] = (unsigned char)(w >> 8);
    m_BITMANINFOHEADER[6] = (unsigned char)(w >> 16);
    m_BITMANINFOHEADER[7] = (unsigned char)(w >> 24);
  
    // bitmap height
    m_BITMANINFOHEADER[8] = (unsigned char)(h);
    m_BITMANINFOHEADER[9] = (unsigned char)(h >> 8);
    m_BITMANINFOHEADER[10] = (unsigned char)(h >> 16);
    m_BITMANINFOHEADER[11] = (unsigned char)(h >> 24);
  }

  typename image_bytes<w, h>::ptr m_image;

  std::array<unsigned char, 14> m_BITMAPFILEHEADER;
  std::array<unsigned char, 40> m_BITMANINFOHEADER;
};
