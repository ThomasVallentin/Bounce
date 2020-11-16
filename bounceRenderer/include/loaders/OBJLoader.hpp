//
// Created by Thomas Vallentin on 29/08/2020.
//

#ifndef BOUNCE_OBJLOADER_HPP
#define BOUNCE_OBJLOADER_HPP

#include "core/FileLoaders.hpp"
#include "shapes/TriangleMesh.hpp"


class OBJLoader: public FileLoader
{
public:
    OBJLoader() : FileLoader() { extension = "obj"; t = Transform::Identity(); };
    explicit OBJLoader(const Transform *trans) : FileLoader() { extension = "obj"; t = trans; };

    bool load(const std::string &path, bool force) override;

    void setTransform(const Transform *trans) { t = trans; }
    const Transform *transform() { return t; }

private:
    const Transform *t;
};


#endif //BOUNCE_OBJLOADER_HPP
