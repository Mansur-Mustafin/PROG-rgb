#ifndef __prog_Image_hpp__
#define __prog_Image_hpp__
#include "Color.hpp"
#include <numeric>
#include <vector>

namespace prog
{
  class Image
  {
  private:
    int w;       // The image's width
    int h;       // The image's height
    Color* img;  // Pointer to 1D array, that storing color of pixels of image
  public:
    // Constructor of image object 
    // w -> width of image
    // h -> height of image
    // fill -> color of all pixels of image
    Image(int w, int h, const Color &fill = {255, 255, 255});

    // Destructor of image object 
    ~Image();

    // Getter the width of the image.
    int width() const;

    // Getter the height of the image.
    int height() const;

    // Return reference to Color at position if image is matrix
    // x -> the column in matrix
    // y -> the row index in matrix
    Color &at(int x, int y);

    // Return constant reference to Color at position if image is matrix
    // x -> the column index in matrix
    // y -> the raw index in matrix
    const Color &at(int x, int y) const;

    // return the media color in segment with center (x, y) and width and height = ws.
    Color media(int x, int y, int ws);

    int histogram_median(std::vector<int>& histogram);
  };
}
#endif
