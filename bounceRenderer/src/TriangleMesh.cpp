#include "TriangleMesh.hpp"

// ===================================================================================
// TRIANGLE MESH
// ===================================================================================
TriangleMeshData::TriangleMeshData(const Transform &objectToWorld,
                                   int nTriangles, int nVertices,
                                   const int *vtxIndices, const Point3 *pnts) :
        nbTriangles(nTriangles), nbVertices(nVertices),
        vertexIndices(vtxIndices, vtxIndices + 3 * nTriangles)
{
    // Creates a Vector3 array based on nbVertices
    points = new Vector3[nVertices];

    // Copying the points of pnts to points
    for (int i = 0; i < nVertices; i++)
    {
        // Bake the transform to the objectSpaced points to make them worldSpaced
        points[i] = pnts[i] * objectToWorld;
    }
}

// ===================================================================================
// TRIANGLE
// ===================================================================================
Triangle::Triangle(const Transform *objectToWorld, const TriangleMeshData *mesh, int triangleNb, Shader *shader)
    : Shape(objectToWorld, shader), mesh(mesh)
{
    vertices = &mesh->vertexIndices[3 * triangleNb];
}


bool Triangle::intersect(const Ray &ray, float tmin, float tmax, HitData &hit) const {
    // Getting the point data
    const Vector3 &p0 = mesh->points[vertices[0]];
    const Vector3 &p1 = mesh->points[vertices[1]];
    const Vector3 &p2 = mesh->points[vertices[2]];

    Vector3 p0p1 = p1 - p0;
    Vector3 p0p2 = p2 - p0;
    Vector3 perpendicularVector = cross(ray.direction, p0p2);
    float determinant = dot(p0p1, perpendicularVector);

    // Testing if the determinant is very close to 0. If so, we skip rendering the triangle
    if (fabsf(determinant) < 1e-8)
        return false;
    // TODO: Implement backface culling

    float invertDeterminant = 1 / determinant;

    // Computing and testing barycentric coordinates :
    // Computing u
    Vector3 tVec = ray.origin - p0;
    float u = dot(tVec, perpendicularVector) * invertDeterminant;
    // Barycentric rule -> u + v + w = 1 for any point in the triangle
    // so if not u < 0 or u > 1, then the hit point is outside the triangle
    if (u < 0 || u > 1)
        return false;

    // Computing v
    Vector3 qVec = cross(tVec, p0p1);
    float v = dot(ray.direction, qVec) * invertDeterminant;
    // Barycentric rule -> u + v + w = 1 for any point in the triangle
    // so if not u < 0 or w(1 - u - v) > 1, then the hit point is outside the triangle
    if (v < 0 || u + v > 1)
        return false;

    float t = dot(p0p2, qVec) * invertDeterminant;
    if (tmin < t && t < tmax) {
        // TODO: Create a proper normal implementation
        Vector3 N = cross(p0p1.normalized(), p0p2.normalized());
        if (dot(ray.direction, N) > 0)
            N *= -1;

        hit.t = t;
        hit.position = ray.pointAtParameter(t);
        hit.normal = N.normalized();

        hit.shader_ptr = shader;
        return true;
    }

    return false;
}