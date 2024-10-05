#include <iostream>
#include "colour.cpp"
#include "bmp.cpp"

int main() {
    const int image_width = 256;
    const int image_height = 256;

    bmpWriter b;

    colour pixels[image_height*image_width];

    for (int j = 0; j < image_height; j++) {
        //std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            
            colour c;

            c.r = i;
            c.g = j;
            c.b = 0;

            pixels[j*image_width + i] = c;
        }
    }

    b.write("test.bmp", pixels, image_width, image_height);
}