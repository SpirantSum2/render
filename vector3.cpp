#include <cmath>

#ifndef VECTOR
#define VECTOR

class vector3{
private:
public:
    double x, y, z; // We're gonna allow the outside to modfy our vector

    vector3(){x=y=y=0.0f;}

    vector3(double xCoord, double yCoord, double zCoord){
        x = xCoord;
        y = yCoord;
        z = zCoord;
    }

    vector3 operator+(vector3 other){
        return vector3(x+other.x, y+other.y, z+other.z);
    }

    vector3 operator-(vector3 other){
        return vector3(x-other.x, y-other.y, z-other.z);
    }

    vector3& operator+=(vector3 other){
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    vector3& operator*=(double multiplier){
        x *= multiplier;
        y *= multiplier;
        z *= multiplier;
        return *this;
    }

    double dot(vector3 other) {
        return x*other.x + y*other.y + z*other.z;
    }

    vector3 cross(vector3 other){
        return vector3(
            y*other.z - other.y*z,
            z*other.x - other.z*x,
            x*other.y - other.x*y
        );
    }

    vector3 normalised(){
        double l = length();
        return vector3(x/l, y/l, z/l);
    }

    double lengthSquared(){
        return x*x + y*y + z*z;
    }

    double length(){
        return sqrt(x*x + y*y + z*z);
    }

};

inline vector3 operator*(double multiplier, vector3 v){
    return vector3(
        v.x * multiplier,
        v.y * multiplier,
        v.z * multiplier
    );
}

#endif