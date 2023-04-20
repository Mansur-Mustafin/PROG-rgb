#ifndef __prog_Color_hpp__
#define __prog_Color_hpp__

namespace prog
{
  typedef unsigned char rgb_value;
  class Color
  {
    private:
      // red, green, blue color channels for color
      rgb_value r;
      rgb_value g;
      rgb_value b;
    public:
      // Default construtor, criates black Color object
      Color();

      // Copy construtor
      Color(const Color& c);

      // Construtor with supplied (red, green, blue) values
      Color(rgb_value r, rgb_value g, rgb_value b);

      
      rgb_value red() const;
      rgb_value& red();
      rgb_value green() const;
      rgb_value& green();
      rgb_value blue() const;
      rgb_value& blue();

      void invert();
  };
}
#endif
