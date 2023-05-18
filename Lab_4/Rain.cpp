#include "Rain.h"

Rain::Rain(unsigned int maximumRain) : m_MaximumRain(maximumRain)
{

    m_RainFallTimer = 240.0f; ///four minutes IRL
    srand(time(0));
}


Rain::~Rain()
{

}


glm::vec3 Rain::getGravity()			  const { return m_Gravity;   }
glm::vec3 Rain::getWindforce()			  const { return m_Windforce; }
std::vector<Particle> Rain::getRaindrop() const { return m_Raindrop;  }
float Rain::getRainDuration()			  const { return m_RainFallTimer;  }



void Rain::setGravity(const glm::vec3& gravity)						{ m_Gravity       = gravity;	   }
void Rain::setWindforce(const glm::vec3& tempWindforce)				{ m_Windforce     = tempWindforce; }
void Rain::setRainParticles(const std::vector<Particle>& particles) { m_Raindrop      = particles;	   }
void Rain::setRainDuration(float tempDuration)						{ m_RainFallTimer = tempDuration;  }




void Rain::update(float deltaTime, glm::vec3 playerLocation)
{
    m_RainFallTimer -= deltaTime;
    
        /// The rain has ended, stop rendering new raindrops.
    if (m_RainFallTimer <= 0.0f)
    {
        return;
    }


    float m_PlayerViewDistance = 100.0f;
    float m_TerrainHeight      = 0.0f;   //Replace with your actual ground level calculation


    for (auto& drop : m_Raindrop)
    {
        drop.m_Position += drop.m_FallRate * deltaTime;
        drop.m_Duration += deltaTime;

     
        if (rainOnGround(drop, m_TerrainHeight))
        {
            // TODO: Add a "wet" mark at the drop's x and z coordinates. 
            // groundTexture.addWetMark(drop.m_Position.x, drop.m_Position.z);
         
            resetRain(&drop);
        }
        else if (rainOutOfView(drop, playerLocation, m_PlayerViewDistance))
        {
            drop.m_Duration = drop.m_Lifetime;
            
            glm::vec3 randomDirection = glm::normalize(glm::vec3(generateRandomFloat(-1.0f, 1.0f), generateRandomFloat(0.0f, 1.0f), generateRandomFloat(-1.0f, 1.0f)));

            float randomDistance = generateRandomFloat(0.0f, m_PlayerViewDistance);

            drop.m_Position = playerLocation + randomDirection * randomDistance;
        }
    }
}



bool Rain::rainOnGround(const Particle& drop, float terrainHeight) const
{
    return drop.m_Position.y <= terrainHeight;
}



bool Rain::rainOutOfView(const Particle& drop, const glm::vec3& playerLocation, float playerViewRadius) const
{
    return drop.m_Duration <= 0.0f || glm::distance(drop.m_Position, playerLocation) > playerViewRadius;
}



float Rain::generateRandomFloat(float min, float max)
{
    float random = ((float)rand()) / (float)RAND_MAX;
    float diff = max - min;
    float r = random * diff;
    return min + r;
}



void Rain::generate(glm::mat4 view, glm::mat4 projection, Shader& shadeRain)
{
    glBindVertexArray(m_VertArrObj);
    shadeRain.use();
    shadeRain.setMat4("view", view);
    shadeRain.setMat4("projection", projection);

    for (const auto& drop : m_Raindrop)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(drop.m_Size));
        shadeRain.setMat4("model", model);
        glDrawArrays(GL_LINES, 0, 2); // Draw raindrop as line
    }
    glBindVertexArray(0);
}




void Rain::triggerRaindrops()
{
    for (auto& drop : m_Raindrop)
    {
        resetRain(&drop);
    }
}




void Rain::resetRain(Particle* particle)
{
    // Reset the properties of the particle
    particle->m_Position = glm::vec3(0.0f);
    particle->m_FallRate = glm::vec3(0.0f, -1.0f, 0.0f); // Assuming raindrops fall downwards
    particle->m_Lifetime = 7.0f; // Assuming a lifetime of 4 seconds for each raindrop
    particle->m_Size = 0.1f; // Assuming a size for the raindrop
    particle->m_Duration = particle->m_Lifetime;
}

