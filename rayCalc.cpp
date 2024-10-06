#include "vector3.cpp"
#include <cmath>
#include <vector>
#include <random>

#ifndef RAYCALC
#define RAYCALC

struct Material{
    vector3 colour;
    vector3 emissionColour;
    double emissionStrength;
};

struct Sphere{
    vector3 centre;
    double radius;
    Material mat;
};

struct HitInfo{
    bool hit;
    vector3 position;
    vector3 normal;
    double distance;
    Material mat;
};

HitInfo raySphere(vector3 rayOrigin, vector3 rayDir, Sphere s){
    HitInfo ret;

    vector3 transformed = s.centre - rayOrigin;

    double b = -2.0 * rayDir.dot(transformed);
    double c = transformed.lengthSquared() - s.radius * s.radius;

    double disc = b*b - 4*c;

    bool hit = disc >= 0;
    ret.hit = hit;

    if (!hit)
        return ret;
    
    // We hit a sphere
    ret.distance = (-b - sqrt(disc))/2 -0.001f;

    if (ret.distance < 0){
        ret.hit = false;
        return ret;
    }

    ret.position = rayOrigin + ret.distance*rayDir;
    ret.normal = (1/s.radius)*(ret.position - s.centre);
    ret.mat = s.mat;

    return ret;
}

HitInfo rayCollsion(vector3 rayOrigin, vector3 rayDir, std::vector<Sphere> spheres){
    HitInfo closest;
    Sphere closestSphere;
    double closestDist = 999999;

    closest.hit = false;

    for (Sphere s : spheres){
        HitInfo h = raySphere(rayOrigin, rayDir, s);
        if (h.hit && h.distance < closestDist){
            closestDist = h.distance;
            closest = h;
            closestSphere = s;
        }
    }

    return closest;
}

vector3 traceRay(vector3 rayOrigin, vector3 rayDir, std::mt19937& gen, std::normal_distribution<double>& rand, std::vector<Sphere>& spheres){
    const int maxBounces = 5;
    vector3 rayColour = vector3(1, 1, 1);
    vector3 lightColour = vector3(0, 0, 0);

    for (int i = 0; i < maxBounces; i++){ // Max of 5 bounces
        HitInfo h = rayCollsion(rayOrigin, rayDir, spheres);
        if(h.hit){
            rayOrigin = h.position;

            // Random direction in the hemisphere of the normal
            rayDir.x = rand(gen);
            rayDir.y = rand(gen);
            rayDir.z = rand(gen);
            rayDir = rayDir.normalised(); 
            if (rayDir.dot(h.normal) < 0)
                rayDir = -1 * rayDir;

            lightColour = lightColour + (h.mat.emissionStrength * h.mat.emissionColour) * rayColour;
            
            rayColour = rayDir.dot(h.normal) * rayColour * h.mat.colour;
        }else{
            vector3 sunDir = vector3(-10, 10, 0).normalised();

            if (sunDir.dot(rayDir) > 0.97){
                lightColour = lightColour + 10*rayColour;
            }else{
                double a = 0.5*(rayDir.y + 1);
                lightColour = lightColour + ((1.0-a)*vector3(1, 1, 1) + a*vector3(0.5, 0.7, 1.0)) * rayColour;
            }


            break;
        }
    }
    return lightColour;
}

#endif