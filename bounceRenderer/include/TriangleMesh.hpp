#ifndef TRIANGLEMESH_HPP
#define TRIANGLEMESH_HPP

#include "HitableComposite.h"
#include "Triangle.hpp"

#include <vector>
#include <memory>


struct TriangleMeshData
{
    TriangleMeshData(int nTriangles, int nVertices, const int *vtxIndices, const vector3 *pnts);
    const int nbTriangles, nbVertices;
    std::vector<int> vertexIndices;
    std::unique_ptr<vector3[]> points;
};

class TriangleMesh : public HitableComposite
{
public:
    TriangleMesh(int nTriangles, int nVertices, const int *vtxIndices, const vector3 *pnts, Shader* shader = nullptr);

private:
    const TriangleMeshData *data;
};

#endif //TRIANGLEMESH_HPP
