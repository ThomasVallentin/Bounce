//
// Created by Thomas Vallentin on 04/08/2020.
// Copyright (c) 2020. All rights reserved.
//

#ifndef BOUNCE_TRANSFORMOBJECT_HPP
#define BOUNCE_TRANSFORMOBJECT_HPP

#include "Transform.hpp"

class TransformObject {
public:
    TransformObject() = default;
    explicit TransformObject(const Transform* objectToWorld) : t(objectToWorld) {}

    const Transform &transform() const { return *t; }
    void setTransform(const Transform *transform) { t = transform; }

protected:
    const Transform *t;
};


#endif //BOUNCE_TRANSFORMOBJECT_HPP
