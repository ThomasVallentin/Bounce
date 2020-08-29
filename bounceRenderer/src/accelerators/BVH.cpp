//
// Created by Thomas Vallentin on 26/08/2020.
//

#include "accelerators/BVH.hpp"

bool BVH::build() {
    buildSubnodes(0, scene->shapes.size());
    return true;
}

bool BVH::intersect(const Ray &ray, float tmin, float tmax, HitData &data) const {
    if (!subnode1 && !subnode2) {
        return scene->shapes[iStart]->intersect(ray, tmin, tmax, data);
    }

    float tMax = tmax;
    bool hasHit = false;

    if (subnode1 && subnode1->bbox.intersect(ray)) {
        hasHit = subnode1->intersect(ray, tmin, tMax, data);
        if (hasHit) {
            tMax = data.t;
        }
    }

    if (subnode2 && subnode2->bbox.intersect(ray)) {
        if (subnode2->intersect(ray, tmin, tMax, data)) {
            hasHit = true;
        }
    }

    return hasHit;
}

bool BVH::intersectAny(const Ray &ray, float tmin, float tmax, HitData &tempdata) const {
    if (!subnode1 && !subnode2) {
        return scene->shapes[iStart]->intersect(ray, tmin, tmax, tempdata);
    }

    float tMax = tmax;
    bool hasHit = false;

    if (subnode1 && subnode1->bbox.intersect(ray)) {
        hasHit = subnode1->intersect(ray, tmin, tMax, tempdata);
        if (hasHit)
            return true;

    }

    if (subnode2 && subnode2->bbox.intersect(ray)) {
        if (subnode2->intersect(ray, tmin, tMax, tempdata))
            return true;
    }

    return hasHit;
}

void BVH::buildSubnodes(const unsigned int &i0, const unsigned int &i1) {
//    std::cout << i0 << " " << i1 << std::endl;
    iStart = i0;
    iEnd = i1;
    subnode1 = nullptr;
    subnode2 = nullptr;
    buildBBox(iStart, iEnd);

    // only contains one face -> return
    if (iEnd == iStart + 1)
        return;

    BoundingBox baryBBox = buildBarycentricBBox(i0, i1);

    // compute diagonal
    Vector3 diagonal = baryBBox.max - baryBBox.min;

    unsigned int splitDimension;
    if (diagonal.x >= diagonal.y && diagonal.x >= diagonal.z)
        splitDimension = 0;
    else if (diagonal.y >= diagonal.x && diagonal.y >= diagonal.z)
        splitDimension = 1;
    else
        splitDimension = 2;

    float splitValue = baryBBox.min[splitDimension] + diagonal[splitDimension] * 0.5f;

    if (diagonal[splitDimension] == 0) {
        subnode1 = new BVH(scene);
        subnode1->buildSubnodes(iStart, (iStart+iEnd)/2 );
        subnode2 = new BVH(scene);
        subnode2->buildSubnodes((iStart+iEnd)/2 , iEnd);
        return;
    }
    // compute max
    float shapePivot;
    unsigned int iSplit = iStart;
    for (size_t i=iStart; i < iEnd; i++) {
        shapePivot = scene->shapes[i]->barycenter()[splitDimension];

        if (shapePivot < splitValue) {
            std::swap(scene->shapes[i], scene->shapes[iSplit]);
            iSplit++;
        }
    }

    // we reach the end of the structure when the split index is inferior as the start index, superior as the end index
    // or if the end index == start index + 1 (there is a single shape in the node)
    if (iSplit == iEnd) {
        return;
    }

    subnode1 = new BVH(scene);
    subnode1->buildSubnodes(iStart, iSplit);
    subnode2 = new BVH(scene);
    subnode2->buildSubnodes(iSplit, iEnd);
}

void BVH::buildBBox(const unsigned int& i0, const unsigned int& i1) {
    bbox = BoundingBox(scene->shapes[i0]->bbox);
    for (size_t i=i0; i < i1; i++) {

        bbox.min.x = std::min(bbox.min.x, scene->shapes[i]->bbox.min.x);
        bbox.min.y = std::min(bbox.min.y, scene->shapes[i]->bbox.min.y);
        bbox.min.z = std::min(bbox.min.z, scene->shapes[i]->bbox.min.z);
        bbox.max.x = std::max(bbox.max.x, scene->shapes[i]->bbox.max.x);
        bbox.max.y = std::max(bbox.max.y, scene->shapes[i]->bbox.max.y);
        bbox.max.z = std::max(bbox.max.z, scene->shapes[i]->bbox.max.z);
    }
}

BoundingBox BVH::buildBarycentricBBox(const unsigned int &i0, const unsigned int &i1) {
    Point3 bary = scene->shapes[i0]->barycenter();
    BoundingBox baryBBox = BoundingBox(bary, bary);
    for (size_t i=i0 + 1; i < i1; i++) {
        bary = scene->shapes[i]->barycenter();

        baryBBox.min.x = std::min(baryBBox.min.x, bary.x);
        baryBBox.min.y = std::min(baryBBox.min.y, bary.y);
        baryBBox.min.z = std::min(baryBBox.min.z, bary.z);
        baryBBox.max.x = std::max(baryBBox.max.x, bary.x);
        baryBBox.max.y = std::max(baryBBox.max.y, bary.y);
        baryBBox.max.z = std::max(baryBBox.max.z, bary.z);
    }

    return baryBBox;
}





