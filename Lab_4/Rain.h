#pragma once

#include <memory>
#include <vector>
#include "Shader.h"
#include "Particle.h"
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>


class Rain
{
    public:
        Rain(unsigned int maximumRain);
        ~Rain();

            // Getter methods
        glm::vec3 getGravity() const;
        glm::vec3 getWindforce() const;
        float getRainDuration() const;
        std::vector<Particle> getRaindrop() const;

            // Setter methods
        void setGravity(const glm::vec3& gravity);
        void setWindforce(const glm::vec3& wind);
        void setRainParticles(const std::vector<Particle>& particles);
        void setRainDuration(float duration);

            // Update method
        void update(float deltaTime, glm::vec3 playerLocation);

            // Helper methods
        bool rainOnGround(const Particle& drop, float terrainHeight) const;
        bool rainOutOfView(const Particle& drop, const glm::vec3& playerLocation, float playerViewRadius) const;
        float generateRandomFloat(float min, float max);

            // Rendering methods
        void generate(glm::mat4 view, glm::mat4 projection, Shader& rainAssetShader);

            // Methods related to raindrop's lifecycle
        void triggerRaindrops();
        void resetRain(Particle* particle);



private:
    
    
    float  m_MaximumRain;
    float  m_RainFallTimer;
    GLuint m_VertArrObj;
    GLuint m_VertBuffObj;

    glm::vec3 m_Gravity;
    glm::vec3 m_Windforce;
    std::vector<Particle> m_Raindrop;
};