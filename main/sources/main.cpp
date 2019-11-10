#include <iostream>
#include <fstream>

#include "RayTracer.h"

using namespace std;

int main() {
	cout << "Hello World, Bounce render !" << endl;
	
	RayTracer tracer(200, 100);
	tracer.setOutpath("D:/REPOSITORIES/Bounce/main/imageOutputs/test_gradient.ppm");

	tracer.trace();

	cout << "Done !";

}
