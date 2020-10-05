//
// Created by Thomas Vallentin on 20/08/2020.
// Copyright (c) 2020. All rights reserved.
//

#include "core/Scene.hpp"

bool Scene::intersect(const Ray& ray, float tmin, float tmax, HitData& data) const
{
    if (accelerator != nullptr)
        return accelerator->intersect(ray, tmin, tmax, data);

    float closest_so_far = tmax;
    bool hit_anything = false;
    HitData temp_data;

    for (Shape *shape : shapes) {
        if (shape->intersect(ray, tmin, closest_so_far, temp_data)) {
            hit_anything = true;
            closest_so_far = temp_data.t;
            data = temp_data;
        }

    }
    return hit_anything;
}

bool Scene::intersectAny(const Ray &ray, float tmin, float tmax) {
    HitData temp_data;

    if (accelerator != nullptr) {
        return accelerator->intersectAny(ray, tmin, tmax, temp_data);
    }

    float closest_so_far = tmax;

    for (Shape *shape : shapes) {
        if (shape->intersect(ray, tmin, closest_so_far, temp_data)) {
            return true;
        }
    }

    return false;
}

