#include <Magick++.h> 
#include <iostream> 
#include <vector>
#include "core.hpp"


struct Point;

int main(int argc,char **argv) { 
    Magick::InitializeMagick(*argv);

    Magick::Image img;
    img.read("1.png");
    img.magick("png");

    int weidth = img.columns();
    int height = img.rows();

    try{
        TypeField obj1(weidth, height);

        obj1.GenerateField(img, 1000000);
        obj1.CreateGraph();
        std::vector<struct Point > res;
        res = obj1.Dsearch({0,0}, {weidth-1, height - 1});
        obj1.Visualization();


        for(int i = 0 ; i < res.size(); i++){
            img.pixelColor(res[i].x, res[i].y, Magick::Color(65535,0,0,65535));
        }
        img.write("2.png");

    }catch(const char * exept){
        std::cerr << exept << std::endl;
    }

    return 0; 
}