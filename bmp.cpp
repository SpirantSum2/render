#include <iostream>
#include <fstream>
#include <cmath>
#include "colour.cpp"

#ifndef BMP_WRITER
#define BMP_WRITER 

class bmpWriter{
private:
    void writeInt(std::ofstream& f, uint32_t toWrite){
        char* a = (char*)(&toWrite);
        f.write(a, 4);
    }
    void writeInt(std::ofstream& f, uint16_t toWrite){
        char* a = (char*)(&toWrite);
        f.write(a, 2);
    }
    void writeInt(std::ofstream& f, uint8_t toWrite){
        char* a = (char*)(&toWrite);
        f.write(a, 1);
    }

    int roundUpTo4Remainder(uint32_t x){
        int remainder = x%4;
        if (remainder)
            return 4-remainder;
        else
            return 0;
    }

public:
    bmpWriter(){}

    void write(const char* filename, colour* colours, uint32_t width, uint32_t height){

        std::ofstream f(filename, std::ios::binary | std::ios::out | std::ios::trunc);

        f.write("BM", 2);
        
        // Account for alignment
        int rowLength = roundUpTo4Remainder(3*width) + 3*width;
        writeInt(f, (uint32_t)(54 + rowLength*height)); // Write the length of the file

        writeInt(f, (uint32_t)0);
        writeInt(f, (uint32_t)54); // Start of pixel array offset

        // DIB header
        writeInt(f, (uint32_t)40); // DIB header size
        writeInt(f, width);
        writeInt(f, height);
        writeInt(f, (uint16_t)1); // Number of colour planes
        writeInt(f, (uint16_t)24); // Bits per pixel
        writeInt(f, (uint32_t)0); // No compression
        writeInt(f, (uint32_t)rowLength*height); // Colour array size
        writeInt(f, (uint32_t)2835); // Real life pixels per metre
        writeInt(f, (uint32_t)2835); // Real life pixels per metre
        writeInt(f, (uint32_t)0); // Number of colours in palette for compression
        writeInt(f, (uint32_t)0); // 0 important colours (all are important)

        // Now we can finally write the colour array
        int paddingSize = roundUpTo4Remainder(width);

        for (int i = height-1; i >= 0; i--){ // Write rows from bottom to top
            for (int j = 0; j < width; j++){
                colour current = colours[i*width + j];

                writeInt(f, current.b);
                writeInt(f, current.g);
                writeInt(f, current.r);
            }
            f.write("help", paddingSize);
        }

        f.close();
    }
};


#endif