#include <iostream>
#include "sdltemplate.h"

int main() {

    // Image

    int image_width = 800;
    int image_height = 400;

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    sdltemplate::sdl("Ray Tracing in One Weekend", image_width, image_height);
    sdltemplate::loop();
    for (int j = image_height -1 ; j >= 00; j--) {
        for (int i = 0; i < image_width; i++) {
            float r = float(i) / float(image_width);
            float g = float(j) / float(image_height);
            float b = 0.2;

            int ir = int(255.999 * r);
            int ig = int(255.999 * g);
            int ib = int(255.999 * b);

            //std::cout << ir << ' ' << ig << ' ' << ib << '\n';
            sdltemplate::setDrawColor(sdltemplate::createColor(ir, ig, ib, 255));
            sdltemplate::drawPoint(i, j);
        }
    }
    while(sdltemplate::running){
        sdltemplate::loop();
    }
}
