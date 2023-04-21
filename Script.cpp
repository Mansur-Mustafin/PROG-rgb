#include <iostream>
#include <fstream>
#include <sstream>
#include "Script.hpp"
#include "PNG.hpp"
#include "XPM2.hpp"
#include "string"
#include "map"

using namespace std;

namespace prog {
    // Use to read color values from a script file.
    istream& operator>>(istream& input, Color& c) {
        int r, g, b;
        input >> r >> g >> b;
        c.red() = r;
        c.green() = g;
        c.blue() = b;
        return input;
    }

    Script::Script(const string& filename) :
            image(nullptr), input(filename) {

    }
    void Script::clear_image_if_any() {
        if (image != nullptr) {
            delete image;
            image = nullptr;
        }
    }
    Script::~Script() {
        clear_image_if_any();
    }

    void Script::run() {
        string command;
        while (input >> command) {
            cout << "Executing command '" << command << "' ..." << endl;
            if (command == "open") {
                open();
                continue;
            }
            if (command == "blank") {
                blank();
                continue;
            }
            // Other commands require an image to be previously loaded.
            if (command == "save") {
                save();
                continue;
            } 
            if (command == "invert"){
                invert();
                continue;
            }
            if (command == "to_gray_scale"){
                to_gray_scale();
                continue;
            }
            if (command == "replace"){
                replace();
                continue;
            }
            if (command == "fill"){
                fill();
                continue;
            }
            if (command == "h_mirror"){
                mirror_h();
                continue;
            }
            if (command == "v_mirror"){
                mirror_v();
                continue;
            }
            if (command == "add"){
                add();
                continue;
            }
            if (command == "crop"){
                crop();
                continue;
            }
            if (command == "rotate_left"){
                rotate_left();
                continue;
            }
            if (command == "rotate_right"){
                rotate_right();
                continue;
            }
            if (command == "median_filter"){
                median_filter();
                continue;
            }
            if (command == "xpm2_open"){
                xpm2_open();
                continue;
            }
            if (command == "xpm2_save"){
                xpm2_save();
                continue;
            }
        }
    }

    void Script::open() {
        // Replace current image (if any) with image read from PNG file.
        clear_image_if_any();
        string filename;
        input >> filename;
        image = loadFromPNG(filename);
    }

    void Script::blank() {
        // Replace current image (if any) with blank image.
        clear_image_if_any();
        int w, h;
        Color fill;
        input >> w >> h >> fill;
        image = new Image(w, h, fill);
    }

    void Script::save() {
        // Save current image to PNG file.
        string filename;
        input >> filename;
        saveToPNG(filename, image);
    }

    void Script::invert(){
        int col_n = image->width();
        int row_n = image->height();

        for(int col = 0; col < col_n; col++){
            for(int row = 0; row < row_n; row++){
                image->at(col, row).invert();
            }
        }
    }

    void Script::to_gray_scale(){
        int col_n = image->width();
        int row_n = image->height();

        for(int col = 0; col < col_n; col++){
            for(int row = 0; row < row_n; row++){
                rgb_value v = image->at(col, row).get_gray();
                Color c = Color(v,v,v);
                image->at(col, row) = c;
            }
        }
    }

    void Script::replace(){
        int r1, g1, b1, r2, g2, b2;

        input >> r1 >> g1 >> b1 >> r2 >> g2 >> b2;

        Color old_color = Color(r1, g1, b1);
        Color new_color = Color(r2, g2, b2);

        int col_n = image->width();
        int row_n = image->height();

        for(int col = 0; col < col_n; col++){
            for(int row = 0; row < row_n; row++){
                if(image->at(col, row) == old_color){
                    image->at(col, row) = new_color;
                }
            }
        }
    }

    void Script::fill(){
        int x, y, w, h, r, g, b;

        input >> x >> y >> w >> h >> r >> g >> b;

        Color new_color = Color(r, g, b);

        int col_max = x + w;
        int row_max = y + h;
        

        for(int col = x; col < col_max; col++){
            for(int row = y; row < row_max; row++){
                image->at(col, row) = new_color;
            }
        }
    }

    void Script::mirror_h(){
        Color tmp = Color();

        int col_n = image->width() / 2;
        int row_n = image->height();
        int w = image->width();

        for(int x = 0; x < col_n; x++){
            for(int y = 0; y < row_n; y++){
                tmp = image->at(x, y);
                image->at(x, y) = image->at(w - 1 - x, y);
                image->at(w - 1 - x, y) = tmp;
            }
        }
    }

    void Script::mirror_v(){
        int col_n = image->width();
        int row_n = image->height() / 2;
        int h = image->height();

        for(int x = 0; x < col_n; x++){
            for(int y = 0; y < row_n; y++){
                swap(image->at(x, y), image->at(x, h - 1 - y));
            }
        }
    }

    void Script::add(){
        // read data
        string filename;
        int x_start, y_start, r, g, b;
        input >> filename;
        input >> r >> g >> b >> x_start >> y_start;
        Color neutral = Color(r, g, b);
        Image *copy_image = loadFromPNG(filename);

        int max_x = copy_image->width();
        int max_y = copy_image->height();

        for(int x = 0; x < max_x; x++){
            for(int y = 0; y < max_y; y++){
                if(!(copy_image->at(x,y) == neutral)){
                    image->at(x_start + x, y_start + y) = copy_image->at(x,y);
                }
            }
        }

        delete copy_image;
    }

    void Script::crop(){
        int x_start, y_start, w, h;
        input >> x_start >> y_start >> w >> h;
        
        Image* copy_image = new Image(w,h);

        for(int x = 0; x < w; x++){
            for(int y = 0; y < h; y++){
                copy_image->at(x,y) = image->at(x_start + x, y_start + y);
            }
        }
        
        Image* tmp = image;
        image = copy_image;
        delete tmp;
    }

    void Script::rotate_left(){
        int w = image->width();
        int h = image->height();
        Image* copy_image = new Image(h,w);

        for(int x = 0; x < w; x++){
            for(int y = 0; y < h; y++){
                copy_image->at(y, w - x - 1) = image->at(x, y);
            }
        }
        

        Image* tmp = image;
        image = copy_image;
        delete tmp;
    }

    void Script::rotate_right(){
        rotate_left();
        rotate_left();
        rotate_left();
    }

    void Script::median_filter(){
        int ws;
        input >> ws;
        int w = image->width();
        int h = image->height();
        Image* copy_image = new Image(w,h);


        for(int x = 0; x < w; x++){
            for(int y = 0; y < h; y++){

                copy_image->at(x,y) = image->media(x, y, ws);
            }
        }
        
        Image* tmp = image;
        image = copy_image;
        delete tmp;
    }

    void Script::xpm2_open(){
        string filename;
        input >> filename;
        Image* copy_image = loadFromXPM2(filename);
        Image* tmp = image;
        image = copy_image;
        delete tmp;
    }

    void Script::xpm2_save(){
        string filename;
        input >> filename;
        saveToXPM2(filename, image);
    }
}
