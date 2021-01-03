#pragma once
#include <glm/glm.hpp>

namespace Rocket
{ 
    class Material
    {
    public:
        Material();
        ~Material();
    protected:
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        float shininess;
    };
}