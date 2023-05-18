#pragma once
#include <vector>
#include <memory>
#include <glm/glm.hpp>


struct Particle 
{
    glm::vec3 m_Position;
    glm::vec3 m_FallRate;
    float     m_Lifetime;
    float     m_Size;
    glm::vec3 m_Colour;
    float     m_Duration;
};

