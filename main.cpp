#include <iostream>
#include "sdltemplate.h"
#include "ray.h"
#include "sphere.h"
#include "hitable_list.h"

// Gradient Implementation of colors
// vec3 color(const ray& r){
//     vec3 unit_dir = unit_vector(r.direction());
//     std::cout << "P3\n" << unit_dir << "\nunit_dir\n";
//     float t = 0.5*(unit_dir.y() + 1.0);
//     std::cout << "P3\n" << t << "\nt\n";
//     return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.0, 0.0, 0.0);
// }

// bool hit_sphere(const vec3 center, float radius, const ray& r){
//     vec3 oc = r.origin() - center;
//     float a = dot(r.direction(), r.direction());
//     float b = 2.0 * dot(oc, r.direction());
//     float c = dot(oc, oc) - radius*radius;
//     float discriminant = b*b - 4*a*c;
//     return (discriminant > 0);
// }

//vec3 sphere, sphere2;
//float sphere_radius;

vec3 color(const ray& r, hitable *world) {
    hit_record rec;
	if(world->hit(r, 0.001, MAXFLOAT, rec)) {
		return 0.5*vec3(rec.normal.x()+1,rec.normal.y()+1,rec.normal.z()+1);
	} else {
		vec3 unit_dir = unit_vector(r.direction());
		float t = 0.5*(unit_dir.y() + 1.0);
		return (1.0-t)*vec3(1.0,1.0,1.0)+t*vec3(0.5,0.7,1.0);
	}
}

int main() {

    // Sphere
    //sphere = vec3(0, 0 , -1);
    //sphere2 = vec3(-0.5, -0.5 , 1);
    //sphere_radius = 0.25;

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
    //vec3 col(0.0, 0.0, 0.0);

    hitable *list[2];
	list[0] = new sphere(vec3(0,0,-1),0.5);
	list[1] = new sphere(vec3(0,-100.5,-1),100);
	hitable *world = new hitable_list(list,2);

    for (int j = image_height -1 ; j >= 00; j--) {
        for (int i = 0; i < image_width; i++) {

            float u = float(i)/float(image_width);
            float v = float(j)/float(image_height);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical);
            vec3 p = r.point_at_parameter(2.0);
			vec3 col = color(r, world);


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
