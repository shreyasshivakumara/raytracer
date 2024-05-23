#include <iostream>
#include "sdltemplate.h"
#include "ray.h"
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"


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

    // Image
    int image_width = 800;
    int image_height = 400;
    int ns = 100;

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    sdltemplate::sdl("Ray Tracing in One Weekend", image_width, image_height);
    sdltemplate::loop();

    hitable *list[2];
	list[0] = new sphere(vec3(0,0,-1),0.5);
	list[1] = new sphere(vec3(0,-100.5,-1),100);
	hitable *world = new hitable_list(list,2);

    camera cam;

    for (int j = image_height -1 ; j >= 00; j--) {
        for (int i = 0; i < image_width; i++) {
            vec3 col(0, 0, 0);
            for (int s = 0; s < ns; s++) {
                float u = float(i + drand48())/float(image_width);
                float v = float(j + drand48())/float(image_height);
                ray r = cam.get_ray(u, v);
                vec3 p = r.point_at_parameter(2.0);
                col += color(r, world);
            }

            col /= float(ns);
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
