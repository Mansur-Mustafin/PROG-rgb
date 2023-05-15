#include "XPM2.hpp"

using namespace std;

namespace prog {
    
    Image* loadFromXPM2(const std::string& file) {
        int w = 0, h = 0, n = 0, x = 0;
        map<char, Color> encode;
        ifstream input_file(file);
        
        string line;
        getline(input_file, line); // ! XPM2
        getline(input_file, line);
        stringstream ss(line);
        ss >> w >> h >> n >> x;
        Image* copy_image = new Image(w,h);
        
        while(n){
            n--;
            getline(input_file, line);
            char key = line[0];
            Color value = Color(line.substr(5));
            encode[key] = value;
        }

        x = 0;
        int y = 0;

        while(getline(input_file, line)){
            for(char c : line){
                if(x >= w) continue;
                copy_image->at(x,y) = encode[c];
                x++;
            }
            x = 0;
            y++;
        }

        return copy_image;
    }

    void saveToXPM2(const std::string& file, const Image* image) {
        ofstream out(file);
        out << "! XPM2" << endl;
        int w = image->width();
        int h = image->height();
        map<Color, char> colors;
        int i = 33;
        
        for(int x = 0; x < w; x++){
            for(int y = 0; y < h; y++){
                if(colors.find(image->at(x,y)) == colors.end()){
                    colors[image->at(x,y)] = (char) i;
                    i++;
                }
            }
        }

        out << w << ' ' << h << ' ' << i - 33 << ' ' << 1 << endl;

        for(auto el: colors){
            out << (char) el.second << " c " << el.first << endl;
        }

        for(int y = 0; y < h; y++){
            for(int x = 0; x < w; x++){
                out << (char) colors[image->at(x,y)];
            }
            out << endl;
        }
        return;
    }
}
