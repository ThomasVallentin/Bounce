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
	tracer.setOutpath("D:\\REPOSITORIES\\Bounce\\main\\imageOutputs\\output.ppm");

	// Shaders
	Shader* redShd = new Lambert(1, 0.1, 0.1);
	Shader* blueShd = new Lambert(0.1, 0.1, .9);
	Shader* yellowShd = new Lambert(0.5, 0.75, 0.1);
	Shader* whiteShd = new Lambert(.8, .8, .8);

	Shader* glassShd = new Glass();

	// Filling the tracer with the objects
	tracer.addHitable(new Sphere(vector3(0.0, 0.0, -2.0), 0.5, "Sphere1", redShd));
	tracer.addHitable(new Sphere(vector3(1.0, 0.0, -2.0), 0.5, "Sphere2", blueShd));
	tracer.addHitable(new Sphere(vector3(-.3, 0.0, -1.2), 0.3, "Sphere3", glassShd));

	// Huge sphere used as pseudo ground
	tracer.addHitable(new Sphere(vector3(0.0, -100.5, -1.0), 100, "Ground", yellowShd));

	// Giving a camera to the trace function
	Camera cam;
	tracer.trace(cam);

	cout << "Done !";

}
