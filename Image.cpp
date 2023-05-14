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

  Color Image::media(int x_start, int y_start, int ws){
    
    std::vector<int> r(256, 0), g(256, 0), b(256, 0);

    int x_init = (0 > (x_start - ws / 2)) ? 0 : (x_start - ws / 2);
    int x_finish = ((w - 1) < (x_start + ws / 2)) ? (w - 1) : (x_start + ws / 2);
    int y_init = (0 > (y_start - ws / 2)) ? 0 : (y_start - ws / 2);
    int y_finish = ((h - 1) < (y_start + ws / 2)) ? (h - 1) : (y_start + ws / 2);

    for(int x = x_init; x <= x_finish; x++){
        for(int y = y_init; y <= y_finish; y++){
            Color c = img[y * w + x];
            r[c.red()]++;
            g[c.green()]++;
            b[c.blue()]++;
        }
    }

    int rm = histogram_median(r);
    int gm = histogram_median(g);
    int bm = histogram_median(b);

    return Color(rm, gm, bm);
}

int Image::histogram_median(std::vector<int>& histogram) {
    int count = std::accumulate(histogram.begin(), histogram.end(), 0);
    int median_index_1 = (count - 1) / 2;
    int median_index_2 = count / 2;

    int median_val_1 = -1;
    int median_val_2 = -1;

    int sum = 0;
    for (size_t i = 0; i < histogram.size(); i++) {
        sum += histogram[i];
        if (sum > median_index_1 && median_val_1 == -1) {
            median_val_1 = i;
        }
        if (sum > median_index_2) {
            median_val_2 = i;
            break;
        }
    }
    return (median_val_1 + median_val_2) / 2;
}

}
