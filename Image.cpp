#include "Image.hpp"

namespace prog
{
  Image::Image(int w, int h, const Color &fill): w(w), h(h)
  {
    int size = w * h;
    img = new Color[size];

    for(int i = 0; i < size; i++){
      img[i] = fill;
    }
  }

  Image::~Image()
  {
    delete[] img;
  }

  int Image::width() const
  {
    return w;
  }

  int Image::height() const
  {
    return h;
  }
  
  Color& Image::at(int x, int y)
  {
    if(x >= 0 && x < w && y >= 0 && y < h) return img[y * w + x];
    else return img[0];
  }

  const Color& Image::at(int x, int y) const
  {
    if(x >= 0 && x < w && y >= 0 && y < h) return img[y * w + x];
    else return img[0];
  }
}
