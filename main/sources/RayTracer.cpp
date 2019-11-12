#include <fstream>
#include <iostream>

#include "RayTracer.h"

vector3 defaultColor(const Ray& ray) {
	vector3 unit_direction = ray.direction().unitVector();
	float t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * vector3(1.0, 1.0, 1.0) + t * vector3(0.5, 0.7, 1.0);
}

vector3 unitToColor(const vector3& vec) {
	return vector3(vec.r() * 255.9, vec.g() * 255.9, vec.b() * 255.9);
}

bool RayTracer::trace()
{
	// opening file stream
	ofstream outputStream(m_outpath);

	// Write ppm format data
	outputStream << "P3\n" << m_width << " " << m_height << "\n255\n";

	vector3 hitcolor(255.0, 0.0, 0.0);

	vector3 cameraOrigin(0.0, 0.0, 0.0);
	vector3 cameraHorizontal(4.0, 0.0, 0.0);
	vector3 cameraVertical(0.0, 2.0, 0.0);
	vector3 cameraLowerLeftCorner(-2.0, -1.0, -1.0);

	// TODO: on inverse l'ecriture des pixels pour le ppm, 
	//       c'est pas propre, il faut trouvber une solution
	for (int y = m_height - 1; y >= 0; y--) {
		for (int x = 0; x < m_width; x++) {
			float u = float(x) / m_width;
			float v = float(y) / m_height;
			Ray ray(cameraOrigin, cameraLowerLeftCorner + u * cameraHorizontal + v * cameraVertical);
			
			vector3 outColor = unitToColor(defaultColor(ray));
			
			for (int k = 0; k < m_objectList.size(); k++) {
				Sphere sph = m_objectList[k];
				float t = sph.isHit(ray);
				if (t > 0.0) {
					// ray hits object in a positive direction
					vector3 hitPoint = ray.pointAtParameter(t);

					vector3 normal = hitPoint - sph.center();
					normal.normalize();

					outColor = unitToColor(0.5 * vector3(normal.x() + 1.0, normal.y() + 1.0, normal.z() + 1.0));
					//outColor = unitToColor(normal + vector3(1.0, 1.0, 1.0));// remapping vector from -1<v<1 to 0<v<1
					//outColor = sph.color();
				}
			}

			outputStream << int(outColor.r()) << " " << int(outColor.g()) << " " << int(outColor.b()) << "\n";

		}

		cout << "Rendering " << (1 - y / float(m_height)) * 100 << "%..." << endl;
	}

	outputStream.close();

	return true;
}
