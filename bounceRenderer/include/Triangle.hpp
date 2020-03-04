#ifndef BOUNCERENDERER_TRIANGLE_HPP
#define BOUNCERENDERER_TRIANGLE_HPP

#include "TriangleMesh.hpp"

class TriangleMeshData;

class Triangle : public Hitable
{
public:
    Triangle(const TriangleMeshData *mesh, int triangleNb, Shader *shader);
    bool intersect(const Ray& ray, float tmin, float tmax, HitData& hit) const override;

protected:
    const TriangleMeshData *mesh; // Pointer to the struct that holds the points
    const int *vertices;  // Pointer to the first vertexIndex of the
};

bool rayTriangleIntersection(const Ray &ray, const vector3 &v0,
                             const vector3 &v1, const vector3 &v2, float &t);

#endif //BOUNCERENDERER_TRIANGLE_HPP
