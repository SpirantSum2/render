#include <iostream>
#include <thread>
#include "colour.cpp"
#include "bmp.cpp"
#include "vector3.cpp" 
#include "rayCalc.cpp"

void render(int threadID, int startRow, int endRow, colour* pixels, const int image_width, const int image_height, const int focalLength, const int raysPerPixel, int* lineCount){
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::normal_distribution<double> rand{0, 1};

    for (int j = startRow; j < endRow; j++) {
        //if (startRow == 0)
        //    std::clog << "\rScanlines remaining for thread 1: " << (endRow - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {

            vector3 rayDir = vector3(i-image_width/2, image_height/2-j, focalLength).normalised(); // Project a width by height plane onto the unit sphere to get the direction of the ray for the pixel
            vector3 c = vector3(0, 0, 0);

            for (int k = 0; k < raysPerPixel; k++){
                rayDir = vector3(i-image_width/2, image_height/2-j, focalLength).normalised();
                c = c + ((double)1/raysPerPixel) * traceRay(vector3(0,0,0), rayDir, gen, rand);
            }

            colour col(c);

            pixels[j*image_width + i] = col;
        }
        lineCount[threadID]--;
    }
}

int main() {
    const int image_width = 1920;
    const int image_height = 1080;
    const int focalLength = 1000;

    const int raysPerPixel = 100;

    const int noThreads = 10;

    int lineCount[noThreads];
    std::vector<std::thread> threads = std::vector<std::thread>();

    bmpWriter b;

    colour pixels[image_height*image_width];

    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::normal_distribution<double> rand{0, 1};

    const int linesPerThread = image_height / noThreads;

    for (int i = 0; i < noThreads; i++){
        lineCount[i] = linesPerThread;
        threads.push_back(std::thread(render, i, i*linesPerThread, (i+1)*linesPerThread, pixels, image_width, image_height, focalLength, raysPerPixel, lineCount));
    }

    int linesRemaining = image_height;

    while (linesRemaining > 0){
        std::clog << "\rScanlines remaining: " << linesRemaining << ' ' << std::flush;
        linesRemaining = 0;
        for (int i = 0; i < noThreads; i++){
            linesRemaining += lineCount[i];
        }
    }
    std::clog << "\rScanlines remaining: " << linesRemaining << ' ' << std::flush;

    for (std::thread &t : threads){
        t.join();
    }

    std::clog << "\nDone" << std::endl;

    b.write("test.bmp", pixels, image_width, image_height);

    return 0;
}