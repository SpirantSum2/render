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
    ret.distance = (-b - sqrt(disc))/2;

    if (ret.distance < 0){
        ret.hit = false;
        return ret;
    }

    ret.position = rayOrigin + ret.distance*rayDir;
    ret.normal = (1/s.radius)*(ret.position - s.centre);
    ret.mat = s.mat;

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

vector3 traceRay(vector3 rayOrigin, vector3 rayDir, std::mt19937& gen, std::normal_distribution<double>& rand){
    Material m1;
    m1.colour = vector3(0, 0, 0);
    m1.emissionColour = vector3(1, 1, 1);
    m1.emissionStrength = 1;
    Material m2;
    m2.colour = vector3(0, 1, 0);
    m2.emissionStrength = 0;
    Material m3;
    m3.colour = vector3(0, 0, 1);
    m3.emissionStrength = 0;
    Sphere s1;
    Sphere s2;
    Sphere s3;
    s1.centre = vector3(-10, 3, 20);
    s1.radius = 15;
    s1.mat = m1;
    s2.centre = vector3(1, -1, 5);
    s2.radius = 1;
    s2.mat = m2;
    s3.centre = vector3(0, -10, 1);
    s3.radius = 9;
    s3.mat = m3;

    std::vector<Sphere> spheres = std::vector<Sphere>();
    //spheres.push_back(s1);
    spheres.push_back(s2);
    spheres.push_back(s3);

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
            
            rayColour = rayColour * h.mat.colour;
        }else{
            vector3 sunDir = vector3(0.5, 1, 1).normalised();

            if (sunDir.dot(rayDir) > 0.95){
                lightColour = lightColour + rayColour;
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