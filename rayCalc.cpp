#include "vector3.cpp"
#include <cmath>
#include <vector>

#ifndef RAYCALC
#define RAYCALC

struct Material{
    vector3 colour;
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
    ret.distance = (-b - sqrt(disc))/2;

    if (ret.distance < 0){
        ret.hit = false;
        return ret;
    }

    ret.position = rayOrigin + ret.distance*rayDir;
    ret.normal = (1/s.radius)*(ret.position - s.centre);

    return ret;
}

vector3 rayColour(vector3 rayOrigin, vector3 rayDir){
    Material m1;
    m1.colour = vector3(1, 0, 0);
    Material m2;
    m2.colour = vector3(0, 1, 0);
    Sphere s1;
    Sphere s2;
    s1.centre = vector3(0, 0, 10);
    s1.radius = 1;
    s1.mat = m1;
    s2.centre = vector3(1, 0, 5);
    s2.radius = 1;
    s2.mat = m2;

    std::vector<Sphere> spheres = std::vector<Sphere>();
    spheres.push_back(s1);
    spheres.push_back(s2);

    HitInfo closest;
    Sphere closestSphere;
    double closestDist = 999999;
    bool hasHit = false;

    for (Sphere s : spheres){
        HitInfo h = raySphere(rayOrigin, rayDir, s);
        if (h.hit && h.distance < closestDist){
            hasHit = true;
            closestDist = h.distance;
            closest = h;
            closestSphere = s;
        }
    }

    if (hasHit){
        return closestSphere.mat.colour;
    }

    double a = 0.5*(rayDir.y + 1);
    return (1.0-a)*vector3(1, 1, 1) + a*vector3(0.5, 0.7, 1.0);
}

#endif