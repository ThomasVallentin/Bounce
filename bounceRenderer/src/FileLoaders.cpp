#include "FileLoaders.hpp"
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

bool FileLoader::load(std::string &path, bool force) {
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

void splitString(const std::string &str, const char token, std::vector<std::string> &splitted)
{
    int curr, previous = 0;
    curr = str.find(token);
    while(curr != std::string::npos)
    {
        splitted.push_back(str.substr(previous, curr - previous));
        previous = curr + 1;
        curr = str.find(token, previous);
    }
    splitted.push_back(str.substr(previous, curr - previous));
}

bool OBJLoader::load(std::string &path, bool force) {
    std::cout << "Loading \"" << path << "\"... ";
    if (!FileLoader::load(path, force))
    {
        return false;
    }

    std::ifstream file(path);

    if (!file.is_open())
    {
        std::cerr << "Couldn't open file \"" << path << "\"" << std::endl;
        return false;
    }

    int nbTriangles(0), nbVertices(0);
    std::vector<int> vertexIndices;
    std::vector<Vector3> positions;

    std::string currentLine;
    std::string token, content;
    int tokenIndex;
    while(std::getline(file, currentLine)) {
        // TODO: Handle multiple polymeshes in file
        tokenIndex = currentLine.find(' ');

        if (tokenIndex < 0)
            continue;

        token = currentLine.substr(0, tokenIndex);
        content = currentLine.substr(tokenIndex + 1);

        if (token == "v")
        {
            // VERTEX POSITION
            Vector3 pos;
            std::vector<std::string> splitted;
            splitString(content, ' ', splitted);

            for(int i=0; i < splitted.size() ; i++)
            {
                pos[i] = std::stof(splitted[i]);
            }

            positions.push_back(pos);
            nbVertices++;
        }
        else if (token == "vn")
        {
            // VERTEX NORMAL
            // TODO: Read vertex normals from obj
        }
        else if (token == "f")
        {
            // FACE
            // TODO: Handle other types of faces than triangles
            std::vector<std::string> splitted;
            splitString(content, ' ', splitted);
            for(std::string &part : splitted)
            {
                std::vector<std::string> subsplitted;
                splitString(part, '/', subsplitted);
                for( int i=0 ; i < subsplitted.size() ; i++ )
                {
                    switch(i)
                    {
                        case 0:  // VERTEX INDEX
                            vertexIndices.push_back(std::stoi(part) - 1);
                            break;

                        case 1:  // TEXTURE COORDINATE INDEX
                            // TODO: Handle tx coordinates reading
                            break;

                        case 2:  // VERTEX NORMAL INDEX
                            // TODO: Handle Vertex normal reading
                            break;

                        default:
                            break;
                    }
                }

            }

            nbTriangles++;
        }

    }

    const TriangleMeshData *meshData = new TriangleMeshData(*t,
                                                            nbTriangles,
                                                            nbVertices,
                                                            vertexIndices.data(),
                                                            positions.data());

    for (int i=0 ; i < nbTriangles ; i++)
    {
        shapes.push_back(new Triangle(t, meshData, i, nullptr));
    }

    std::cout << "Loaded !" << std::endl;

    return true;
}
