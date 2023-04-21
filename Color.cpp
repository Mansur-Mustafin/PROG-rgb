#include "Color.hpp"


namespace prog {
    Color::Color(): r(0), g(0), b(0) {} // black

    Color::Color(const Color& other): r(other.r), g(other.g), b(other.b) {} // copy constr

    Color::Color(rgb_value red, rgb_value green, rgb_value blue): r(red), g(green), b(blue) {} // constr by (r, g, b)

    // convert hex to deimal
    int getInt(char c){  
        if (c >= '0' && c <= '9') {
            return c - '0';
        } else if (c >= 'A' && c <= 'F') {
            return c - 'A' + 10;
        } else if (c >= 'a' && c <= 'f') {
            return c - 'a' + 10;
        }
        return 0;
    }

    Color::Color(std::string str){
        this->r = getInt(str[0]) * 16 + getInt(str[1]);
        this->g = getInt(str[2]) * 16 + getInt(str[3]);
        this->b = getInt(str[4]) * 16 + getInt(str[5]);
    }

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

    // ADDED FUNCTIONS

    void Color::invert(){
        r = 255 - r;
        g = 255 - g;
        b = 255 - b;
    }

    rgb_value Color::get_gray(){
        rgb_value v = (r + g + b) / 3;
        return v;
    }

    bool Color::operator==(const Color& right) const
    {
    return (r == right.r) && (g == right.g) && (b == right.b);
    }

    
}