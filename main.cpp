#include <iostream>
#include <thread>
#include "colour.cpp"
#include "bmp.cpp"
#include "vector3.cpp" 
#include "rayCalc.cpp"
#include "scenes.cpp"

void render(int threadID, int noThreads, colour* pixels, const int image_width, const int image_height, const int focalLength, const int raysPerPixel, int* lineCount){
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::normal_distribution<double> norm{0, 1};
    std::uniform_real_distribution<double> offset{-0.5, 0.5};

    Scene s = cornell();
    std::vector<Sphere> spheres = s.spheres;
    std::vector<Triangle> triangles = s.triangles;


    for (int j = threadID; j < image_height; j += noThreads) { // Distribute work equally amongst all threads
        //if (startRow == 0)
        //    std::clog << "\rScanlines remaining for thread 1: " << (endRow - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {

            vector3 rayDir;
            vector3 c = vector3(0, 0, 0);

            for (int k = 0; k < raysPerPixel; k++){
                rayDir = vector3(i-image_width/2 + offset(gen), image_height/2-j + offset(gen), focalLength).normalised();  // Project a width by height plane onto the unit sphere to get the direction of the ray for the pixel
                c = c + ((double)1/raysPerPixel) * traceRay(vector3(0,0,0), rayDir, gen, norm, spheres, triangles);
            }

            colour col(c);

            pixels[j*image_width + i] = col;
        }
        lineCount[threadID]--;
    }
}

int main() {
    const int image_width = 1024;
    const int image_height = 1024;
    const int focalLength = 2813;

    const int raysPerPixel = 200;

    const int noThreads = 10;

    int lineCount[noThreads];
    std::vector<std::thread> threads = std::vector<std::thread>();

    bmpWriter b;

    colour pixels[image_height*image_width];

    const int linesPerThread = image_height / noThreads;

    for (int i = 0; i < noThreads; i++){
        lineCount[i] = linesPerThread;
        threads.push_back(std::thread(render, i, noThreads, pixels, image_width, image_height, focalLength, raysPerPixel, lineCount));
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