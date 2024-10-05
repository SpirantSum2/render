#include <iostream>
#include "colour.cpp"
#include "bmp.cpp"
#include "vector3.cpp" 
#include "rayCalc.cpp"

int main() {
    const int image_width = 960;
    const int image_height = 540;
    const int focalLength = 500;

    const int raysPerPixel = 5;

    bmpWriter b;

    colour pixels[image_height*image_width];

    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::normal_distribution<double> rand{0, 1};


    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {

            vector3 rayDir = vector3(i-image_width/2, image_height/2-j, focalLength).normalised(); // Project a width by height plane onto the unit sphere to get the direction of the ray for the pixel
            vector3 c = vector3(0, 0, 0);

            for (int k = 0; k < raysPerPixel; k++){
                rayDir = vector3(i-image_width/2, image_height/2-j, focalLength).normalised();
                c = c + 0.2 * traceRay(vector3(0,0,0), rayDir, gen, rand);
            }

            colour col(c);

            pixels[j*image_width + i] = col;
        }
    }
    std::clog << "\nDone" << std::endl;

    b.write("test.bmp", pixels, image_width, image_height);
}