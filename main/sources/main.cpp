#include <iostream>
#include <fstream>

#include "RayTracer.h"

using namespace std;

int main() {
	cout << "Hello World, Bounce render !" << endl;
	
	RayTracer tracer(400, 200);
	tracer.setOutpath("D:/REPOSITORIES/Bounce/main/imageOutputs/test_gradient.ppm");

	Sphere sph(vector3(0.0, 0.0, -1.0), 0.5);
	sph.setColor(255.0, 0.0, 0.0);

	tracer.addSphere(sph);
	//cout << tracer.ls()[0].center();
	tracer.trace();

	cout << "Done !";

}
