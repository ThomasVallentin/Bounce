#ifndef BOUNCERENDERER_FILELOADERS_HPP
#define BOUNCERENDERER_FILELOADERS_HPP

#include "TriangleMesh.hpp"
#include "Camera.hpp"

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
    OBJLoader() : FileLoader() { extension = "obj"; t = Transform::Identity(); };
    OBJLoader(const Transform *trans) : FileLoader() { extension = "obj"; t = trans; };

    bool load(std::string &path, bool force) override;

    void setTransform(const Transform *trans) { t = trans; }
    const Transform *transform() { return t; }

private:
    const Transform *t;
};


#endif //BOUNCERENDERER_FILELOADERS_HPP
