#ifndef BOUNCERENDERER_FILELOADERS_HPP
#define BOUNCERENDERER_FILELOADERS_HPP

#include "TriangleMesh.hpp"
#include <map>

// New type -> pointer to a readFile function
//typedef std::vector<Hitable*> *readFileFunction (std::string);
//
//
//std::map<std::string, readFileFunction> extensionToReader;
//
//std::vector<Hitable*> readAlembic(const std::string &path);

struct FileLoaders
{
    std::vector<std::string> extensions;
    std::vector<Hitable*> (*read)(std::string &path);
};

std::vector<Hitable*> readAlembic(std::string &path);

static FileLoaders AlembicReader = {{".abc"}, readAlembic};

std::vector<Hitable*> readFromFile(std::string &path);

#endif //BOUNCERENDERER_FILELOADERS_HPP
