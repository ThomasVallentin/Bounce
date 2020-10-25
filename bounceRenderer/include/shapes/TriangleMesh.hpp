#ifndef TRIANGLEMESH_HPP
#define TRIANGLEMESH_HPP

#include "core/Point3.hpp"
#include "core/Shape.hpp"
#include "core/mathUtils.h"

#include <vector>
#include <memory>

extern int intersectCount;

struct TriangleMeshData {
    TriangleMeshData(const Transform &objectToWorld,
                     int nTriangles, int nVertices,
                     const int *vtxIndices, const Point3 *pnts,
                     const int *normIndices, const Vector3 *norms);

    bool hasVertexNormal() const { return (normals != nullptr); }
    const int nbTriangles, nbVertices;
    std::vector<int> vertexIndices, normalIndices;
    Point3* points;
    Vector3* normals;
};


class Triangle : public Shape
{
public:
    Triangle(const Transform *objectToWorld, const TriangleMeshData *mesh, int triangleNb, Material *material);
    bool intersect(const Ray& ray, float tmin, float tmax, HitData& hit) const override;
    void buildBBox() override;
    Point3 barycenter() const override;
    float area() const override;

protected:
    const TriangleMeshData *mesh; // Pointer to the struct that holds the points
    const int *vertices;  // Pointer to the first vertexIndex of the triangle
    const int *normals;  // Pointer to the first normalIndex of the triangle
};


#endif //TRIANGLEMESH_HPP
