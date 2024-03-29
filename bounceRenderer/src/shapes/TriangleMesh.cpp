#include "shapes/TriangleMesh.hpp"
#include "core/Constants.hpp"

// ===================================================================================
// TRIANGLE MESH
// ===================================================================================
TriangleMeshData::TriangleMeshData(const Transform &objectToWorld,
                                   const int &nTriangles, const int &nPoints, const int &nNormals,
                                   const int *vtxIndices, const Point3 *pnts,
                                   const int *normIndices, const Vector3 *norms) :
        nTriangles(nTriangles), nPoints(nPoints), nNormals(nNormals),
        vertexIndices(vtxIndices, vtxIndices + 3 * nTriangles),
        normalIndices(normIndices, normIndices + 3 * nTriangles)
{
    // Creates a Vector3 array based on nbVertices
    points = new Point3[nPoints];

    // Copy points
    for (int i = 0; i < nPoints; i++)
        points[i] = pnts[i] * objectToWorld;  // Bake points in worldSpace

    // Copy normals
    if (norms == nullptr)
        normals = nullptr;
    else {
        normals = new Vector3[nNormals];

        for (int i = 0; i < nNormals; i++) {
            normals[i] = (norms[i] * objectToWorld).normalized();  // Bake normals in worldSpace
        }
    }
}

// ===================================================================================
// TRIANGLE
// ===================================================================================
Triangle::Triangle(const Transform *objectToWorld, const TriangleMeshData *mesh, int triangleNb, Material *shader)
    : Shape(objectToWorld, shader), mesh(mesh)
{
    vertices = &mesh->vertexIndices[3 * triangleNb];
    normals = &mesh->normalIndices[3 * triangleNb];
}


bool Triangle::intersect(const Ray &ray, float tmin, float tmax, HitData &hit) const {
    intersectCount += 1;
    // Getting the point data
    const Point3 &p0 = mesh->points[vertices[0]];
    const Point3 &p1 = mesh->points[vertices[1]];
    const Point3 &p2 = mesh->points[vertices[2]];

    Vector3 p0p1 = p1 - p0;
    Vector3 p0p2 = p2 - p0;
    Vector3 perpendicularVector = cross(ray.direction, p0p2);
    float determinant = dot(p0p1, perpendicularVector);

    // Testing if the determinant is very close to 0. If so, we skip rendering the triangle
    if (fabsf(determinant) < 1e-9)
        return false;

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
        Vector3 N;
        if ( mesh->hasVertexNormal() ) {
            Vector3 n0 = mesh->normals[normals[0]];
            Vector3 n1 = mesh->normals[normals[1]];
            Vector3 n2 = mesh->normals[normals[2]];

            N = n0*(1 - u - v) + n1*u + n2*v;

            // If vertex normal is empty -> compute face normal
            if (N.x == 0 && N.y == 0 && N.z == 0) {
                N = cross(p0p1, p0p2);
                if (dot(ray.direction, N) > 0)
                    N *= -1;
                N.normalize();
            }

        } else {
            N = cross(p0p1, p0p2);
//            if (dot(ray.direction, N) > 0)
//                N *= -1;
            N.normalize();
        }

        hit.t = t;
        hit.position = ray.pointAtParameter(t);
        hit.normal = N;
        makeCoordinateSystem(hit.normal, hit.tan1, hit.tan2);
        hit.wo = ray.direction * -1;
        hit.material = material;
        return true;
    }

    return false;
}

void Triangle::buildBBox() {
    const Point3 &p0 = mesh->points[vertices[0]];
    const Point3 &p1 = mesh->points[vertices[1]];
    const Point3 &p2 = mesh->points[vertices[2]];

    bbox = BoundingBox(std::min(std::min(p0.x, p1.x), p2.x),
                       std::min(std::min(p0.y, p1.y), p2.y),
                       std::min(std::min(p0.z, p1.z), p2.z),
                       std::max(std::max(p0.x, p1.x), p2.x),
                       std::max(std::max(p0.y, p1.y), p2.y),
                       std::max(std::max(p0.z, p1.z), p2.z));
}

Point3 Triangle::barycenter() const {
    return (mesh->points[vertices[0]] + mesh->points[vertices[1]] + mesh->points[vertices[2]]) / 3.0f;
}

float Triangle::area() const {
    Point3 &A = mesh->points[vertices[0]];
    Point3 &B = mesh->points[vertices[1]];
    Point3 &C = mesh->points[vertices[2]];
    return cross(B - A, C - A).length() * 0.5f;
}

