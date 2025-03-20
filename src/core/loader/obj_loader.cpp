#include <core/loader/obj_loader.h>

#include <fstream>
#include <sstream>
#include <vector>

using namespace Core::Loader;

Core::Resources::Mesh ParseOBJFile(const std::string& file_path)
{
    // Core::Resources::Mesh mesh;

    // std::ifstream file(file_path);
    // std::string line;

    // std::vector<Core::Math::Vector4> pos;
    // std::vector<Core::Math::Vector3> normal;
    // std::vector<Core::Math::Vector2> texcoord;

    // while (std::getline(file, line))
    // {   
    //     std::istringstream iss(line);
    //     std::string type;
    //     iss >> type;
    // }
}

std::map<std::string, Core::Resources::Material> ParseMTLFile(const std::string& file_path)
{

}