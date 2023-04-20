#include "Color.hpp"

namespace prog {
    Color::Color(): r(0), g(0), b(0) {} // black

    Color::Color(const Color& other): r(other.r), g(other.g), b(other.b) {} // copy constr

    Color::Color(rgb_value red, rgb_value green, rgb_value blue): r(red), g(green), b(blue) {} // constr by (r, g, b)

    rgb_value Color::red() const {
        return r;
    }
    rgb_value Color::green() const {
        return g;
    }
    rgb_value Color::blue() const {
        return b;
    }

    // TODO: remove this DUMMY variable once you have appropriate fields for representing colors.
    rgb_value DUMMY_rgb_value = 0; 

    rgb_value& Color::red()  {
        return this->r;
    }
    rgb_value& Color::green()  {
      return this->g;
    }
    rgb_value& Color::blue()  {
      return this->b;
    }
}