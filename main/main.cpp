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
	tracer.setOutpath("D:/REPOSITORIES/Bounce/main/imageOutputs/output.ppm");

	//sph.setColor(255.0, 0.0, 0.0);

	// Filling the tracer with the objects
	tracer.addHitable(new Sphere(vector3(0.0, 0.0, -1.0), 0.5, "Sphere"));
	tracer.addHitable(new Sphere(vector3(1.0, 0.0, -1.0), 0.5, "Sphere"));
	//tracer.addHitable(new Sphere(vector3(0.75, 0.0, -1.0), 0.5));

	// Huge sphere used as pseudo ground
	tracer.addHitable(new Sphere(vector3(0.0, -100.5, -1.0), 100, "Ground"));

	// Giving a camera to the trace function
	Camera cam;
	tracer.trace(cam);

	cout << "Done !";

}
