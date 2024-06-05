#include <iostream>
#include <cstdlib>
#include "sdltemplate.h"
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include "material.h"
#include "planes.h"
#include <fstream>



bool russian_roulette(float probability) {
    return ((float) rand() / RAND_MAX) < probability;
}

vec3 color(const ray& r, hitable *world, int depth) {
    hit_record rec;
    if (world->hit(r, 0.001, MAXFLOAT, rec)) {
        ray scattered;
        vec3 attenuation;
        vec3 emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);

        // Russian Roulette termination
        if (depth >= 50) {
            return emitted;
        }

        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            float probability = 0.3; // Adjust this value to change the probability of termination
            if (russian_roulette(probability)) {
                vec3 next_color = color(scattered, world, depth + 1);
                return emitted + attenuation * next_color / probability;
            } else {
                return emitted;
            }
        } else {
            return emitted;
        }
    } else {
        vec3 unit_dir = unit_vector(r.direction());
        float t = 0.5 * (unit_dir.y() + 1.0);
        return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    }
}

int main() {

    // Image
    int image_width = 600;
    int image_height = 400;
    int ns = 10;

    // Color
     // Define materials
    material* lambertian_material = new lambertian(vec3(0.5, 0.5, 0.8));
    material* metal_material = new metal(vec3(0.8, 0.8, 0.8), 0.3);
    material* dielectric_material = new dielectric(1.5);
    material* emissive_material = new emissive(vec3(1.0, 1.0, 1.0));

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    sdltemplate::sdl("Ray Tracing", image_width, image_height);
    sdltemplate::loop();

    float plane_size = 2.0; // Size of the planes
    hitable *list[6];
    int i = 0;
    list[i++] = new sphere(vec3(0, 0,-1), 0.5, metal_material);
    list[i++] = new sphere(vec3(0,-100.5,-1), 100, lambertian_material);
    list[i++] = new sphere(vec3(1, 0, -1),0.5, dielectric_material);
    list[i++] = new sphere(vec3(-1, 0, -1), 0.5, emissive_material);
    // list[i++] = new plane(vec3(1, 0, -1), vec3(1, 0, 0), lambertian_material, plane_size);    // Floor
    // list[i++] = new plane(vec3(-1, 0, -1), vec3(-1, 0, 0), lambertian_material, plane_size);
    // list[i++] = new plane(vec3(0, 0, -1), vec3(0, 0, 1), lambertian_material, plane_size);
    // list[i++] = new plane(vec3(0, 1, -1), vec3(0, -1, 0), emissive_material, plane_size);
    // list[i++] = new plane(vec3(0, -1, -1), vec3(0, 1, 0), emissive_material, plane_size);

    hitable *world = new hitable_list(list,i);

    camera cam(vec3(0,0,1), vec3(0,0,-1), vec3(0,1,0), 60, float(image_width)/float(image_height));

    std::ofstream outfile("output/output.ppm");
    outfile << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height -1 ; j >= 00; j--) {
        for (int i = 0; i < image_width; i++) {
            vec3 col(0, 0, 0);
            for (int s = 0; s < ns; s++) {
                float u = float(i + drand48())/float(image_width);
                float v = float(j + drand48())/float(image_height);
                ray r = cam.get_ray(u, v);
                vec3 p = r.point_at_parameter(8.0);
                col += color(r, world, 0);
            }

            col /= float(ns);
            col = vec3(sqrt(col.r()),sqrt(col.g()),sqrt(col.b()));
            int ir = int(255.999 * col[0]);
            int ig = int(255.999 * col[1]);
            int ib = int(255.999 * col[2]);

            // Write the color to the output file
            outfile << ir << ' ' << ig << ' ' << ib << '\n';

            //std::cout << ir << ' ' << ig << ' ' << ib << '\n';
            sdltemplate::setDrawColor(sdltemplate::createColor(ir, ig, ib, 255));
            sdltemplate::drawPoint(i, image_height - j);
        }
    }
    
    outfile.close(); // Close the output file

    while(sdltemplate::running){
        sdltemplate::loop();
    }
}

