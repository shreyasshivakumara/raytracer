#include <iostream>
#include "sdltemplate.h"
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include "material.h"
<<<<<<< HEAD

vec3 color(const ray& r, hitable *world, int depth) {
	hit_record rec;
	if(world->hit(r, 0.001, MAXFLOAT, rec)) {
		ray scattered;
		vec3 attenuation;
		if(depth < 50 && rec.mat_ptr->scatter(r,rec,attenuation,scattered)) {
			return attenuation*color(scattered,world,depth+1);
		} else {
			return vec3(0,0,0);
		}
=======
#include "planes.h"

vec3 color(const ray& r, hitable *world, int depth) {
    hit_record rec;
	if(world->hit(r, 0.001, MAXFLOAT, rec)) {
        // Normal vectors can range -1 to 1 and +1 is added to normalize it.
        // Lambert Implementation
        // vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		// return 0.5*color(ray(rec.p,target-rec.p),world);
        ray scattered;
        vec3 attenuation;
        vec3 emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);
        // Maximum depth of recursion
        if(depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            // Recursion to get the color of the scattered ray here
            vec3 temp = color(scattered, world, depth+1);
            vec3 result = emitted + attenuation*temp;
            return result;
        } else {
            //return vec3(0,0,0);
            return emitted;
        }
>>>>>>> cornell_box
	} else {
		vec3 unit_dir = unit_vector(r.direction());
		float t = 0.5*(unit_dir.y() + 1.0);
		return (1.0-t)*vec3(1.0,1.0,1.0)+t*vec3(0.5,0.7,1.0);
	}
}


int main() {
<<<<<<< HEAD
	//sphere = vec3(0,0,-1);
	//sphere_radius = 0.5;
	int width = 800;
	int height = 400;
	int ns = 100;
	std::cout << "P3\n" << width << " " << height << "\n255\n";
	sdltemplate::sdl("Ray Tracer", width, height);
	sdltemplate::loop();
	hitable *list[4];
	list[0] = new sphere(vec3(0,0,-1),0.5,new lambertian(vec3(0.8,0.3,0.3)));
	list[1] = new sphere(vec3(0,-100.5,-1),100,new lambertian(vec3(0.8,0.8,0.0)));
	list[2] = new sphere(vec3(1,0,-1),0.5,new metal(vec3(0.8,0.6,0.2),0.2));
	list[3] = new sphere(vec3(-1,0,-1),0.5,new metal(vec3(0.8,0.8,0.8),0.7));
	hitable *world = new hitable_list(list,4);
	camera cam;
	for(int y=height-1; y>=0; y--) {
		for(int x=0; x<width; x++) {
			vec3 col(0,0,0);
			for(int s=0;s<ns;s++) {
				float u = float(x+drand48()) / float(width);
				float v = float(y+drand48()) / float(height);
				ray r = cam.get_ray(u,v);
				vec3 p = r.point_at_parameter(2.0);
				col += color(r, world, 0);
			}
			col /= float(ns);
			col = vec3(sqrt(col.r()),sqrt(col.g()),sqrt(col.b()));
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			//std::cout << ir << " " << ig << " " << ib << "\n";
			sdltemplate::setDrawColor(sdltemplate::createColor(ir,ig,ib,255));
			sdltemplate::drawPoint(x,height-y);
		}
	}
	while(sdltemplate::running) {
		sdltemplate::loop();
	}
}
=======

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
    hitable *list[5];
    int i = 0;
    list[i++] = new sphere(vec3(0, 0,-1), 0.5, metal_material);
    //list[i++] = new sphere(vec3(0,-100.5,-1), 100, lambertian_material);
    //list[i++] = new sphere(vec3(1, 0, -1),0.5, metal_material);
    //list[i++] = new sphere(vec3(-1, 0, -1), 0.5, emissive_material);   // Left wall
    list[i++] = new plane(vec3(1, 0, -1), vec3(1, 0, 0), lambertian_material, plane_size);    // Floor
    list[i++] = new plane(vec3(-1, 0, -1), vec3(-1, 0, 0), lambertian_material, plane_size);
    list[i++] = new plane(vec3(0, 1, -1), vec3(0, -1, 0), emissive_material, plane_size);
    list[i++] = new plane(vec3(0, -1, -1), vec3(0, 1, 0), emissive_material, plane_size);

    hitable *world = new hitable_list(list,i);

    camera cam(vec3(0,0,1.1), vec3(0,0,-1), vec3(0,1,0), 60, float(image_width)/float(image_height));

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

            //std::cout << ir << ' ' << ig << ' ' << ib << '\n';
            sdltemplate::setDrawColor(sdltemplate::createColor(ir, ig, ib, 255));
            sdltemplate::drawPoint(i, image_height - j);
        }
    }
    while(sdltemplate::running){
        sdltemplate::loop();
    }
}







//EMITS SPHERE AS A LIGHT SOURCE
// vec3 color(const ray& r, hitable *world, int depth) {
//     hit_record rec;
//     if(world->hit(r, 0.001, MAXFLOAT, rec)) {
//         ray scattered;
//         vec3 attenuation;
//         vec3 emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);
//         if(depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
//             return emitted + attenuation*color(scattered, world, depth+1);
//         } else {
//             return emitted;
//         }
//     } else {
//         return vec3(0,0,0);
//     }
// }
>>>>>>> cornell_box
