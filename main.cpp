#include <iostream>
#include "colour.cpp"
#include "bmp.cpp"
#include "vector3.cpp" 

int main() {
    const int image_width = 1920;
    const int image_height = 1080;

    bmpWriter b;

    colour pixels[image_height*image_width];

    for (int j = 0; j < image_height; j++) {
        //std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {

            vector3 rayDir = vector3(i, 0, j).normalised(); // Project a width by height plane onto the unit sphere to get the direction of the ray for the pixel

            colour c(rayDir);

            pixels[j*image_width + i] = c;
        }
    }

    b.write("test.bmp", pixels, image_width, image_height);
}