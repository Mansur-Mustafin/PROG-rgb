#ifndef __prog_XPM2_hpp__
#define __prog_XPM2_hpp__

#include <string>
#include "Image.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Script.hpp"
#include "XPM2.hpp"
#include "string"
#include <map>
#include <set>

namespace prog {
    Image* loadFromXPM2(const std::string &file);

    void saveToXPM2(const std::string& file, const Image* img);
}
#endif
