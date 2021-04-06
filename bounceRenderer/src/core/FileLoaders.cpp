#include "core/FileLoaders.hpp"
#include <iomanip>

bool getFileExtension(const std::string &path, std::string &extension)
{
    std::string filename = path.substr(path.find_last_of('/') + 1);
    std::string ext = filename.substr(filename.find_last_of('.') + 1);

    // If ext == filename, it means that we didnt find any '.' in the string -> no extension
    if (ext == filename)
    {
        std::cerr << "Couldn't find the a valid file extension from \"" << path << "\"." << std::endl;
        return (false);
    }

    extension = ext;
    return (true);
}

bool FileLoader::load(const std::string &path, bool force) {
    std::cout << "Loading \"" << path << "\"... ";

    shapes.clear();
    lights.clear();
    cameras.clear();

    if (!force) {
        std::string ext;
        if (getFileExtension(path, ext)) {
            if (ext == extension) {
                return true;
            } else {
                std::cerr << "Unvalid file type, expected \"" << extension << "\" got \"" << ext << "\"" << std::endl;
            }
        }
    }

    return false;
}
