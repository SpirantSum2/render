#include <iostream>
#include "colour.cpp"
#include "bmp.cpp"
#include "vector3.cpp" 
#include "rayCalc.cpp"

int main() {
    const int image_width = 1920;
    const int image_height = 1080;
    const int focalLength = 1000;

    bmpWriter b;

    colour pixels[image_height*image_width];

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {

            vector3 rayDir = vector3(i-image_width/2, image_height/2-j, focalLength).normalised(); // Project a width by height plane onto the unit sphere to get the direction of the ray for the pixel

            colour c(rayColour(vector3(0,0,0), rayDir));

            pixels[j*image_width + i] = c;
        }
    }
    std::clog << "\nDone" << std::endl;

    b.write("test.bmp", pixels, image_width, image_height);
}