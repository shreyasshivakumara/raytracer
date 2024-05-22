#include <iostream>
#include "sdltemplate.h"
#include "ray.h"

// Gradient Implementation of colors
// vec3 color(const ray& r){
//     vec3 unit_dir = unit_vector(r.direction());
//     std::cout << "P3\n" << unit_dir << "\nunit_dir\n";
//     float t = 0.5*(unit_dir.y() + 1.0);
//     std::cout << "P3\n" << t << "\nt\n";
//     return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.0, 0.0, 0.0);
// }

bool hit_sphere(const vec3 center, float radius, const ray& r){
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0 * dot(oc, r.direction());
    float c = dot(oc, oc) - radius*radius;
    float discriminant = b*b - 4*a*c;
    return (discriminant > 0);
}

vec3 sphere, sphere2;
float sphere_radius;

vec3 color(const ray& r){
    if(hit_sphere(sphere, sphere_radius, r)) return vec3(1, 0, 0);
    if(hit_sphere(sphere2, sphere_radius, r)) return vec3(0, 1, 0);
    vec3 unit_dir = unit_vector(r.direction());
    float t = 0.5*(unit_dir.y() + 1.0);
    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}

int main() {

    // Sphere
    sphere = vec3(0, 0 , -1);
    sphere2 = vec3(-0.5, -0.5 , 1);
    sphere_radius = 0.25;

    // Image

    int image_width = 800;
    int image_height = 400;

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    sdltemplate::sdl("Ray Tracing in One Weekend", image_width, image_height);
    sdltemplate::loop();

    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);
    vec3 col(0.0, 0.0, 0.0);


    for (int j = image_height -1 ; j >= 00; j--) {
        for (int i = 0; i < image_width; i++) {

            float u = float(i)/float(image_width);
            float v = float(j)/float(image_height);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical);
            vec3 col = color(r);
            //vec3 col(float(i) / float(image_width), float(j) / float(image_height), 0.2);
            //float r = float(i) / float(image_width);
            //float g = float(j) / float(image_height);
            //float b = 0.2;

            int ir = int(255.999 * col[0]);
            int ig = int(255.999 * col[1]);
            int ib = int(255.999 * col[2]);

            //std::cout << ir << ' ' << ig << ' ' << ib << '\n';
            sdltemplate::setDrawColor(sdltemplate::createColor(ir, ig, ib, 255));
            sdltemplate::drawPoint(i, j);
        }
    }
    while(sdltemplate::running){
        sdltemplate::loop();
    }
}
