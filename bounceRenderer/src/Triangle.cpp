#include "Triangle.hpp"

Triangle::Triangle(const TriangleMeshData *mesh, int triangleNb, Shader *shader) :
        Hitable(), mesh(mesh)
{
    vertices = &mesh->vertexIndices[3 * triangleNb];
    shader_ptr = shader;
}

bool Triangle::intersect(const Ray &ray, float tmin, float tmax, HitData &hit) const {
    // Getting the point data
    const vector3 &p0 = mesh->points[vertices[0]];
    const vector3 &p1 = mesh->points[vertices[1]];
    const vector3 &p2 = mesh->points[vertices[2]];

    vector3 p0p1 = p1 - p0;
    vector3 p0p2 = p2 - p0;
    vector3 perpendicularVector = cross(ray.direction, p0p2);
    float determinant = dot(p0p1, perpendicularVector);

    // Testing if the determinant is very close to 0. If so, we skip rendering the triangle
    if (fabsf(determinant) < 1e-8)
        return false;
    // TODO: Implement backface culling

    float invertDeterminant = 1 / determinant;

    // Computing and testing barycentric coordinates :
    // Computing u
    vector3 tVec = ray.origin - p0;
    float u = dot(tVec, perpendicularVector) * invertDeterminant;
    // Barycentric rule -> u + v + w = 1 for any point in the triangle
    // so if not u < 0 or u > 1, then the hit point is outside the triangle
    if (u < 0 || u > 1)
        return false;

    // Computing v
    vector3 qVec = cross(tVec, p0p1);
    float v = dot(ray.direction, qVec) * invertDeterminant;
    // Barycentric rule -> u + v + w = 1 for any point in the triangle
    // so if not u < 0 or w(1 - u - v) > 1, then the hit point is outside the triangle
    if (v < 0 || u + v > 1)
        return false;

    float t = dot(p0p2, qVec) * invertDeterminant;
    if (tmin < t && t < tmax) {
        // TODO: Create a proper normal implementation
        vector3 N = cross(p0p1.unitVector(), p0p2.unitVector());
        if (dot(ray.direction, N) > 0)
            N *= -1;

        hit.t = t;
        hit.position = ray.pointAtParameter(t);
        hit.normal = N;
        hit.shader_ptr = shader_ptr;
        return true;
    }

    return false;
}