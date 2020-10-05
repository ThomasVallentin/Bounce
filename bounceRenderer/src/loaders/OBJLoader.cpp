//
// Created by Thomas Vallentin on 29/08/2020.
//

#include "loaders/OBJLoader.hpp"

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

bool OBJLoader::load(const std::string &path, bool force) {
    if (!FileLoader::load(path, force))
        return false;

    std::ifstream file(path);

    if (!file.is_open())
    {
        std::cerr << "Couldn't open file \"" << path << "\"" << std::endl;
        return false;
    }

    int nbTriangles(0), nbVertices(0);
    std::vector<int> vertexIndices, normalIndices;
    std::vector<Point3> positions;
    std::vector<Vector3> normals;

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
            Point3 pos;
            std::vector<std::string> splitted;
            splitString(content, ' ', splitted);

            pos.x = std::stof(splitted[0]);
            pos.y = std::stof(splitted[1]);
            pos.z = std::stof(splitted[2]);

            positions.push_back(pos);
            nbVertices++;
        }
        else if (token == "vn")
        {
//            std::cout << "vn"  << std::endl;
            // VERTEX NORMAL
            Vector3 norm;
            std::vector<std::string> splitted;
            splitString(content, ' ', splitted);

            norm.x = std::stof(splitted[0]);
            norm.y = std::stof(splitted[1]);
            norm.z = std::stof(splitted[2]);

            normals.push_back(norm.normalized());
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
                            vertexIndices.push_back(std::stoi(subsplitted[i]) - 1);
                            break;

                        case 1:  // TEXTURE COORDINATE INDEX
                            // TODO: Handle tx coordinates reading
                            break;

                        case 2:  // VERTEX NORMAL INDEX
                            normalIndices.push_back(std::stoi(subsplitted[i]) - 1);
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
                                                            positions.data(),
                                                            normalIndices.data(),
                                                            normals.data());

    for (int i=0 ; i < nbTriangles ; i++)
    {
        shapes.push_back(new Triangle(t, meshData, i, nullptr));
    }

    std::cout << "Loaded !" << std::endl;

    return true;
}