#include <iostream>
#include <fstream>

#include "RayTracer.h"
#include "Sphere.h"

using namespace std;

int main() {
	cout << "Hello World, Bounce render !" << endl;
	
	int output_width = 400;
	int output_height = 200;
	float near_clip = 0.001;
	float far_clip = 100000;
	int samples = 100;

	RayTracer tracer(output_width, output_height, near_clip, far_clip, samples);
	tracer.setOutpath("D:/REPO/Bounce/main/imageOutputs/output.ppm");

	// Shaders
	Shader* groundShd = new Lambert(0.7, 0.6, 0.2);
	Shader* shinyRedShd = new SurfaceShader(0.7, 0.2, 0.2, 0.15);
	Shader* roughBlueShd = new SurfaceShader(0.2, 0.2, 0.8, 0.9);

	// Filling the tracer with the objects
	tracer.addHitable(new Sphere(vector3(0.0, 0.0, -1.0), 0.5, "Sphere1", shinyRedShd));
	tracer.addHitable(new Sphere(vector3(1.0, 0.0, -1.0), 0.5, "Sphere2", roughBlueShd));
	//tracer.addHitable(new Sphere(vector3(0.75, 0.0, -1.0), 0.5));

	// Huge sphere used as pseudo ground
	tracer.addHitable(new Sphere(vector3(0.0, -100.5, -1.0), 100, "Ground", groundShd));

	// Giving a camera to the trace function
	Camera cam;
	tracer.trace(cam);

	cout << "Done !";

}
