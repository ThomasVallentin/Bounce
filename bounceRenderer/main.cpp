#include "RayTracer.h"
#include "Sphere.h"
#include "Ray.h"

#include <iostream>

int main() {
    std::cout << "Hello World, Bounce render !" << std::endl;

    int output_width = 1200;
    int output_height = 600;
    float near_clip = 0.001;
    float far_clip = 100000;
    int samples = 100;

    RayTracer tracer(output_width, output_height, near_clip, far_clip, samples);
    tracer.setOutpath(R"(D:\REPOSITORIES\Bounce\bounceRenderer\output\output.ppm)");

    // Shaders
    std::vector<Shader*> shaders;
    for (unsigned char i=0; i < 25; i++) {
        shaders.push_back(new Lambert(randomFlt(), randomFlt(), randomFlt()));
        shaders.push_back(new Metal(randomFlt(), randomFlt(), randomFlt(), randomFlt()));
        shaders.push_back(new Metal(randomFlt(), randomFlt(), randomFlt(), randomFlt()));
        shaders.push_back(new Metal(randomFlt(), randomFlt(), randomFlt(), randomFlt()));
    }

    Shader* groundShd = new Lambert(0.5, 0.75, 0.1);
    Shader* glassShd = new Glass();

    vector3 pos;
    float size;
    Sphere* sph;
    for (unsigned char i=0; i < 25; i++){
        size = randomFlt(0, 0.2);
        pos = vector3(randomFlt(-1, 1)*10, size/2-0.25f, -(randomFlt() * 20 + 1));
        sph = new Sphere(pos, randomFlt(), "Sphere", shaders[rand() % shaders.size()]);
        tracer.addHitable(sph);
    }

    // Huge sphere used as pseudo ground
    tracer.addHitable(new Sphere(vector3(0.0, -1000.5, -1.0), 1000, "Ground", groundShd));

    // Giving a camera to the trace function
    Camera cam;
    tracer.initialize();
    tracer.trace(cam);

    return (EXIT_SUCCESS);
}
