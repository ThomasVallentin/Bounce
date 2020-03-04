#include "TriangleMesh.hpp"

TriangleMeshData::TriangleMeshData(int nTriangles,
                           int nVertices,
                           const int *vtxIndices,
                           const vector3 *pnts) :
        nbTriangles(nTriangles), nbVertices(nVertices),
        vertexIndices(vtxIndices, vtxIndices + 3 * nTriangles)
{
    // Creates a vector3 array based on nbVertices
    points = std::make_unique<vector3[]>(nVertices);

    // Copying the points of pnts to points
    for (int i = 0; i < nVertices; i++)
    {
        points[i] = vector3(pnts[i]);
    }
}

TriangleMesh::TriangleMesh(int nTriangles,
                           int nVertices,
                           const int *vtxIndices,
                           const vector3 *pnts) : HitableComposite()
{
    data = new TriangleMeshData( nTriangles, nVertices, vtxIndices, pnts );
    for (int i = 0 ; i < nTriangles ; i++ )
    {
        m_hitableList.push_back(new Triangle(data, i, shader_ptr));
    }
}
