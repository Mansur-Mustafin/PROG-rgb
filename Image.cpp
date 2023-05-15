#include "Image.hpp"
#include "vector"
#include "algorithm"
#include "iostream"

namespace prog
{
  using std::vector;
  using std::sort;

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

  Color Image::media(int x_start, int y_start, int ws)
  {  
    vector<rgb_value> r, g, b;
    
    int x_init = std::max(0, x_start - ws / 2);
    int x_finish = std::min(w - 1, x_start + ws / 2);
    int y_init = std::max(0, y_start - ws / 2);
    int y_finish = std::min(h - 1, y_start + ws / 2);

    for(int x = x_init; x <= x_finish; x++){
      for(int y = y_init; y <= y_finish; y++){
        Color c = img[y * w + x];
        r.push_back(c.red());
        g.push_back(c.green());
        b.push_back(c.blue());
      }
    }

    std::sort(r.begin(), r.end());
    std::sort(g.begin(), g.end());
    std::sort(b.begin(), b.end());
    
    size_t size = r.size();

    if(size % 2 == 0){
      int rm = r[size / 2] + r[size / 2 - 1]; 
      int gm = g[size / 2] + g[size / 2 - 1]; 
      int bm = b[size / 2] + b[size / 2 - 1]; 
      return Color(rm / 2, gm / 2, bm / 2);
    }

    int index = r.size() / 2;
    return Color(r[index], g[index], b[index]);
  }
}
