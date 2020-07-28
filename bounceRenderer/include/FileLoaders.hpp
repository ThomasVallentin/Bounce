#ifndef BOUNCERENDERER_FILELOADERS_HPP
#define BOUNCERENDERER_FILELOADERS_HPP

#include "TriangleMesh.hpp"
#include "Camera.h"

#include <map>
#include <fstream>

class FileLoader
{
public:
    FileLoader() = default;
    virtual bool load(std::string &path, bool force);
    std::vector<Shape*> shapes;
    std::vector<Shape*> lights;
    std::vector<Camera*> cameras;

protected:
    std::string extension;
};

class OBJLoader: public FileLoader
{
public:
    OBJLoader() : FileLoader() { extension = "obj"; };
    bool load(std::string &path, bool force) override;
};


#endif //BOUNCERENDERER_FILELOADERS_HPP
