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

struct Triangle{
    vector3 origin;
    vector3 edge1;
    vector3 edge2;
    vector3 normal;
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
    ret.distance = (-b - sqrt(disc))/2 - 0.001f;

    if (ret.distance < 0){
        ret.hit = false;
        return ret;
    }

    ret.position = rayOrigin + ret.distance*rayDir;
    ret.normal = (1/s.radius)*(ret.position - s.centre);
    ret.mat = s.mat;

    return ret;
}

HitInfo rayTriangle(vector3 rayOrigin, vector3 rayDir, Triangle tri){ // Möller–Trumbore algorithm implementation from wikipedia
    HitInfo ret;

    double epsilon = std::numeric_limits<double>::epsilon();

    vector3 rayCrossE2 = rayDir.cross(tri.edge2);
    double det = tri.edge1.dot(rayCrossE2);

    if (det > -epsilon && det < epsilon){
        ret.hit = false;
        return ret;
    }

    double invDet = 1.0f/det;
    vector3 s = rayOrigin - tri.origin;
    double u = invDet * s.dot(rayCrossE2);

    if (u < 0 || u > 1){
        ret.hit = false;
        return ret;
    }

    vector3 sCrossE1 = s.cross(tri.edge1);
    double v = invDet * rayDir.dot(sCrossE1);

    if (v < 0 || u + v > 1){
        ret.hit = false;
        return ret;
    }

    ret.distance = invDet * tri.edge2.dot(sCrossE1) - 0.001f;

    if (ret.distance < 0){
        ret.hit = false;
        return ret;
    }

    ret.hit = true;
    
    if (tri.normal.dot(rayDir) < 0)
        ret.normal = tri.normal;
    else
        ret.normal = -1 * tri.normal;

    ret.mat = tri.mat;
    ret.position = rayOrigin + (ret.distance * rayDir);

    return ret;
}

HitInfo rayCollsion(vector3 rayOrigin, vector3 rayDir, std::vector<Sphere> spheres, std::vector<Triangle> triangles){
    HitInfo closest;
    Sphere closestSphere;
    double closestDist = 999999;

    closest.hit = false;

    for (Sphere s : spheres){
        HitInfo h = raySphere(rayOrigin, rayDir, s);
        if (h.hit && h.distance < closestDist){
            closestDist = h.distance;
            closest = h;
        }
    }

    for (Triangle t : triangles){
        HitInfo h = rayTriangle(rayOrigin, rayDir, t);
        if (h.hit && h.distance < closestDist){
            closestDist = h.distance;
            closest = h;
        }
    }

    return closest;
}

vector3 traceRay(vector3 rayOrigin, vector3 rayDir, std::mt19937& gen, std::normal_distribution<double>& rand, std::vector<Sphere>& spheres, std::vector<Triangle>& triangles){
    const int maxBounces = 5;
    vector3 rayColour = vector3(1, 1, 1);
    vector3 lightColour = vector3(0, 0, 0);

    for (int i = 0; i < maxBounces; i++){ // Max of 5 bounces
        HitInfo h = rayCollsion(rayOrigin, rayDir, spheres, triangles);
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
            /*
            vector3 sunDir = vector3(-10, 10, 0).normalised();

            if (sunDir.dot(rayDir) > 0.97){
                lightColour = lightColour + 10*rayColour;
            }else{
                double a = 0.5*(rayDir.y + 1);
                lightColour = lightColour + ((1.0-a)*vector3(1, 1, 1) + a*vector3(0.5, 0.7, 1.0)) * rayColour;
            }
            */
           //lightColour = rayColour + lightColour;
            break;
        }
    }
    return lightColour;
}

#endif