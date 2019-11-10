#include <iostream>
#include <fstream>
#include "ray.h"

using namespace std;

int main() {
	cout << "Hello World, Bounce render !" << endl;
	int xMax = 200;
	int yMax = 100;

	ofstream imageStream("D:/REPOSITORIES/Bounce/main/imageOutputs/test_gradient.ppm");

	imageStream << "P3\n" << xMax << " " << yMax << "\n255\n";

	for (int y = 0; y < yMax; y++) {
		for (int x = 0; x < xMax; x++) {
			vector3 color(float(x) / float(xMax) * 255.99,
				float(y) / float(yMax) * 255.99,
				0.2 * 255.99);

			imageStream << int(color.r()) << " " << int(color.g()) << " " << int(color.b()) << "\n";
			
		}

		cout << "Rendering " << y / float(yMax) * 100 << "%..." << endl;
	}

	cout << "Done!";

}
