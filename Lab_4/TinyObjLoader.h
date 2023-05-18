#pragma once

#include <vector>

struct TinyObjDLoader
{
    std::vector<float> vertices;
    std::vector<float> texcoords;
    std::vector<float> normals;
    std::vector<unsigned int> indices;
};