#include <iostream>
#include "vector3.cpp"
#ifndef COLOUR
#define COLOUR

struct colour{
    uint8_t r;
    uint8_t g;
    uint8_t b;

    colour(){r=g=b=0;}

    colour(vector3 c){ // Convert a vector with values in 0-1 to a colour
        r = c.x*255.99;
        g = c.y*255.99;
        b = c.z*255.99;
    }

    colour(uint8_t red, uint8_t green, uint8_t blue){
        r = red;
        g = green;
        b = blue;
    }

    colour (double red, double green, double blue){ // Make a colour with values from 0 to 1
        r = red*255.99;
        g = green*255.99;
        b = blue*255.99;
    }
};

#endif