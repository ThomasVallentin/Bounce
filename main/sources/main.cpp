#include <iostream>
#include <fstream>
#include "vector3.h"

using namespace std;

int main() {
	cout << "Hello World, Bounce render !" << endl;
	int xMax = 200;
	int yMax = 100;

	ofstream imageStream("D:/REPOSITORIES/Bounce/main/imageOutputs/test_gradient.ppm");

	imageStream << "P3\n" << xMax << " " << yMax << "\n255\n";

	for (int y = 0; y < yMax; y++) {
		for (int x = 0; x < xMax; x++) {
		
			int r = float(x) / float(xMax) * 255.99;
			int g = float(y) / float(yMax) * 255.99;
			int b = 0.2 * 255.99;

			imageStream << r << " " << g << " " << b << "\n";
		}
	}
}