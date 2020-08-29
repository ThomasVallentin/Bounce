#ifndef TRIANGLEMESH_HPP
#define TRIANGLEMESH_HPP

#include "Point3.hpp"
#include "Shape.hpp"

#include <vector>
#include <memory>

extern int intersect_count;

struct TriangleMeshData {
    TriangleMeshData(const Transform &objectToWorld,
                     int nTriangles, int nVertices,
                     const int *vtxIndices, const Point3 *pnts);

    const int nbTriangles, nbVertices;
    std::vector<int> vertexIndices;
    Point3* points;
};


class Triangle : public Shape
{
public:
    Triangle(const Transform *objectToWorld, const TriangleMeshData *mesh, int triangleNb, Shader *shader);
    bool intersect(const Ray& ray, float tmin, float tmax, HitData& hit) const override;
    void buildBBox() override;
    Point3 barycenter() override;

protected:
    const TriangleMeshData *mesh; // Pointer to the struct that holds the points
    const int *vertices;  // Pointer to the first vertexIndex of the triangle
};


#endif //TRIANGLEMESH_HPP
