//
// Created by Thomas Vallentin on 19/10/2020.
//

#include "shapes/Disc.hpp"

bool Disc::intersect(const Ray &ray, float tmin, float tmax, HitData &hitdata) const {
    float parameter;
    Vector3 N(t->matrix.m[2][0], t->matrix.m[2][1], t->matrix.m[2][2]);

    if (!intersectDisk(ray, N, radius,
                       Point3(t->matrix.m[3][0], t->matrix.m[3][1], t->matrix.m[3][2]), parameter))
        return false;

    if (parameter <= tmin || parameter >= tmax)
        return false;

    hitdata.t = parameter;
    hitdata.position = ray.pointAtParameter(parameter);
    hitdata.normal = N;
    makeCoordinateSystem(hitdata.normal, hitdata.tan1, hitdata.tan2);
    hitdata.wo = ray.direction * -1;
    hitdata.material = material;
    return true;
}

Point3 Disc::barycenter() const {
    return Point3(t->matrix.m[3][0], t->matrix.m[3][1], t->matrix.m[3][2]);
}

void Disc::buildBBox() {
    Point3 bary = barycenter();
    bbox = BoundingBox(bary.x - radius,
                       bary.y - radius,
                       bary.z - radius,
                       bary.x + radius,
                       bary.y + radius,
                       bary.z + radius);
}

HitData Disc::sample(float &pdf) const {
    HitData hitdata;

    hitdata.position = (randomPointInUnitCircle() * radius);
    hitdata.position *= *t;

    hitdata.normal = Vector3(t->matrix.m[2][0], t->matrix.m[2][1], t->matrix.m[2][2]);
    hitdata.material = material;

    pdf = samplePdf(hitdata);
    return hitdata;
}

float Disc::area() const {
    return PI * radius * radius;
}
