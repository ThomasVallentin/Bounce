#ifndef BOUNCERENDERER_FILELOADERS_HPP
#define BOUNCERENDERER_FILELOADERS_HPP

#include "core/Shape.hpp"
#include "Camera.hpp"

#include <map>
#include <vector>
#include <fstream>

class FileLoader
{
public:
    FileLoader() = default;
    virtual bool load(const std::string &path, bool force);
    std::vector<Shape*> shapes;
    std::vector<Shape*> lights;
    std::vector<Camera*> cameras;

protected:
    std::string extension;
};


#endif //BOUNCERENDERER_FILELOADERS_HPP
