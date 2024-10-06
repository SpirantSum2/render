#include <vector>
#include "rayCalc.cpp"
#include "vector3.cpp"

#ifndef SCENES
#define SCENES

struct Scene{
    std::vector<Sphere> spheres;
    std::vector<Triangle> triangles;
};

Scene sphereScene(){
    Material m1;
    m1.colour = vector3(1, 1, 1);
    m1.emissionStrength = 0;
    Material m2;
    m2.colour = vector3(0, 1, 0);
    m2.emissionStrength = 0;
    Material m3;
    m3.colour = vector3(0, 0, 1);
    m3.emissionStrength = 0;
    Material m4;
    m4.colour = vector3(0, 1, 1);
    m4.emissionStrength = 0;
    Sphere s1;
    Sphere s2;
    Sphere s3;
    Sphere s4;
    s1.centre = vector3(0.3, -1.3, 4);
    s1.radius = 0.7f;
    s1.mat = m1;
    s2.centre = vector3(1, -1, 5);
    s2.radius = 1;
    s2.mat = m2;
    s3.centre = vector3(0, -6.5, 4);
    s3.radius = 5;
    s3.mat = m3;
    s4.centre = vector3(-0.6, -1.5, 3.4);
    s4.radius = 0.5;
    s4.mat = m4;

    std::vector<Sphere> spheres = std::vector<Sphere>();
    spheres.push_back(s1);
    spheres.push_back(s2);
    spheres.push_back(s3);
    spheres.push_back(s4);

    std::vector<Triangle> triangles = std::vector<Triangle>();

    Scene s;
    s.spheres = spheres;
    s.triangles = triangles;

    return s;
}

Scene cornell(){
    Material red;
    red.colour = vector3(0.63, 0.05, 0.05);
    red.emissionStrength = 0;
    red.reflectance = 0;

    Material green;
    green.colour = vector3(0.12, 0.45, 0.15);
    green.emissionStrength = 0;
    green.reflectance = 0;

    Material white;
    white.colour = vector3(0.73, 0.73, 0.73);
    white.emissionStrength = 0;
    white.reflectance = 0;

    Material light;
    light.colour = vector3(0, 0, 0);
    light.emissionColour = vector3(1, 1, 1);
    light.emissionStrength = 10;
    light.reflectance = 0;

    Material mirror;
    mirror.colour = vector3(1, 1, 1);
    mirror.emissionStrength = 0;
    mirror.reflectance = 1;

    Material frostedMirror;
    frostedMirror.colour = vector3(1, 1, 1);
    frostedMirror.emissionStrength = 0;
    frostedMirror.reflectance = 0.5;

    Triangle t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14;
    t1.origin = vector3(-0.37, -0.37, 2.74);
    t1.edge1 = vector3(0, 0, -0.74);
    t1.edge2 = vector3(0, 0.74, 0);
    t1.normal = vector3(1, 0, 0);
    t1.mat = red;

    t2.origin = vector3(-0.37, 0.37, 2);
    t2.edge1 = vector3(0, -0.74, 0);
    t2.edge2 = vector3(0, 0, 0.74);
    t2.normal = vector3(1, 0, 0);
    t2.mat = red;

    t3.origin = vector3(0.37, -0.37, 2.74);
    t3.edge1 = vector3(0, 0, -0.74);
    t3.edge2 = vector3(0, 0.74, 0);
    t3.normal = vector3(-1, 0, 0);
    t3.mat = green;

    t4.origin = vector3(0.37, 0.37, 2);
    t4.edge1 = vector3(0, -0.74, 0);
    t4.edge2 = vector3(0, 0, 0.74);
    t4.normal = vector3(-1, 0, 0);
    t4.mat = green;

    t5.origin = vector3(-0.37, -0.37, 2);
    t5.edge1 = vector3(0, 0, 0.74);
    t5.edge2 = vector3(0.74, 0, 0);
    t5.normal = vector3(0, 1, 0);
    t5.mat = white;

    t6.origin = vector3(0.37, -0.37, 2.74);
    t6.edge1 = vector3(-0.74, 0, 0);
    t6.edge2 = vector3(0, 0, -0.74);
    t6.normal = vector3(0, 1, 0);
    t6.mat = white;

    t7.origin = vector3(-0.37, 0.37, 2);
    t7.edge1 = vector3(0, 0, 0.74);
    t7.edge2 = vector3(0.74, 0, 0);
    t7.normal = vector3(0, -1, 0);
    t7.mat = white;

    t8.origin = vector3(0.37, 0.37, 2.74);
    t8.edge1 = vector3(-0.74, 0, 0);
    t8.edge2 = vector3(0, 0, -0.74);
    t8.normal = vector3(0, -1, 0);
    t8.mat = white;

    t9.origin = vector3(-0.37, -0.37, 2.74);
    t9.edge1 = vector3(0, 0.74, 0);
    t9.edge2 = vector3(0.74, 0, 0);
    t9.normal = vector3(0, 0, -1);
    t9.mat = white;

    t10.origin = vector3(0.37, 0.37, 2.74);
    t10.edge1 = vector3(0, -0.74, 0);
    t10.edge2 = vector3(-0.74, 0, 0);
    t10.normal = vector3(0, 0, -1);
    t10.mat = white;
    
    t11.origin = vector3(-0.185, 0.36, 2.185);
    t11.edge1 = vector3(0, 0, 0.37);
    t11.edge2 = vector3(0.37, 0, 0);
    t11.normal = vector3(0, -1, 0);
    t11.mat = light;

    t12.origin = vector3(0.185, 0.36, 2.555);
    t12.edge1 = vector3(0, 0, -0.37);
    t12.edge2 = vector3(-0.37, 0, 0);
    t12.normal = vector3(0, -1, 0);
    t12.mat = light;
    
    t13.origin = vector3(0.37, 0.37, 2);
    t13.edge1 = vector3(0, -0.74, 0);
    t13.edge2 = vector3(-0.74, 0, 0);
    t13.normal = vector3(0, 0, 1);
    t13.mat = white;

    t14.origin = vector3(-0.37, -0.37, 2);
    t14.edge1 = vector3(0.74, 0, 0);
    t14.edge2 = vector3(0, 0.74, 0);
    t14.normal = vector3(0, 0, 1);
    t14.mat = white;

    std::vector<Triangle> triangles = std::vector<Triangle>();
    triangles.push_back(t1);
    triangles.push_back(t2);
    triangles.push_back(t3);
    triangles.push_back(t4);
    triangles.push_back(t5);
    triangles.push_back(t6);
    triangles.push_back(t7);
    triangles.push_back(t8);
    triangles.push_back(t9);
    triangles.push_back(t10);
    triangles.push_back(t11);
    triangles.push_back(t12);
    triangles.push_back(t13);
    triangles.push_back(t14);

    Sphere s1, s2;
    s1.centre = vector3(-0.16, -0.215, 2.5);
    s1.radius = 0.15;
    s1.mat = mirror;

    s2.centre = vector3(0.16, -0.215, 2.5);
    s2.radius = 0.15;
    s2.mat = frostedMirror;

    std::vector<Sphere> spheres = std::vector<Sphere>();
    spheres.push_back(s1);
    spheres.push_back(s2);

    Scene s;
    s.triangles = triangles;
    s.spheres = spheres;

    return s;
}

#endif