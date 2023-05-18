#include "SpecialKeys.h"


SpecialKeys::SpecialKeys() 
{

}


SpecialKeys::~SpecialKeys()
{

}

void SpecialKeys::toggleWireframeMode()
{
    wireframe = !wireframe;

    if (wireframe) 
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else 
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}



void SpecialKeys::triggerFlying()
{
    isFlying = !isFlying;


    // perhaps at this point we get an instance of the Player from the engine and modify there isFlying bool variable?
    // Then main game loop calls update() on player, which would then be responsible for grounding the camera on the terrain floor?

    auto m_camera = LabEngine::getInstance().m_camera;
    m_camera->canFly = !m_camera->canFly;


    /*
    auto simpleTerrain = LabEngine::getInstance().simpleTerrain;
    auto m_camera = LabEngine::getInstance().m_camera;


    float scaleOffSetX = 1 / simpleTerrain->scaleX;
    float scaleOffSetZ = 1 / simpleTerrain->scaleZ;
    float newY = 0.0f;

    glm::vec3 Position = m_camera->getCameraLocation();

    if (!isFlying)
    {
        newY = simpleTerrain->getHeight((int)Position.x * scaleOffSetX, (int)Position.z * scaleOffSetZ);
        Position.y = newY + 1.3;
        m_camera->setCameraLocation(Position);
    }
    */
    std::cout << isFlying << std::endl;
}


void SpecialKeys::handleKeyEntered(GLFWwindow* m_PixelsGLFWWindow, int key, bool& keyState, void (SpecialKeys::* action)())
{
    if (glfwGetKey(m_PixelsGLFWWindow, key) == GLFW_PRESS && !keyState)
    {
        (this->*action)();
        keyState = true;
    }
    else if (glfwGetKey(m_PixelsGLFWWindow, key) == GLFW_RELEASE)
    {
        keyState = false;
    }
}


void SpecialKeys::F_KeyEntered(GLFWwindow* m_PixelsGLFWWindow)
{
    handleKeyEntered(m_PixelsGLFWWindow, GLFW_KEY_F, keyStates[GLFW_KEY_F], &SpecialKeys::triggerFlying);
}


void SpecialKeys::K_KeyEntered(GLFWwindow* m_PixelsGLFWWindow)
{
    handleKeyEntered(m_PixelsGLFWWindow, GLFW_KEY_K, keyStates[GLFW_KEY_K], &SpecialKeys::toggleWireframeMode);
}


void SpecialKeys::L_KeyEntered(GLFWwindow* m_PixelsGLFWWindow)
{
    handleKeyEntered(m_PixelsGLFWWindow, GLFW_KEY_L, keyStates[GLFW_KEY_L], &SpecialKeys::toggleLighting);
}


void SpecialKeys::M_KeyEntered(GLFWwindow* m_PixelsGLFWWindow)
{
    handleKeyEntered(m_PixelsGLFWWindow, GLFW_KEY_M, keyStates[GLFW_KEY_M], &SpecialKeys::displayDemoWindow);
}


void SpecialKeys::X_KeyEntered(GLFWwindow* m_PixelsGLFWWindow)
{
    handleKeyEntered(m_PixelsGLFWWindow, GLFW_KEY_X, keyStates[GLFW_KEY_X], &SpecialKeys::displayGroupPhoto);
}


void SpecialKeys::displayDemoWindow()
{
   // gui->show_demo_window = !gui->show_demo_window;
    auto gui = LabEngine::getInstance().gui;
    gui->show_demo_window = !gui->show_demo_window;
}



void SpecialKeys::displayGroupPhoto()
{
    auto gui = LabEngine::getInstance().gui;
    gui->show_image = !gui->show_image;
}



void SpecialKeys::toggleLighting()
{
    bool lightingEnabled = true;

    lightingEnabled = !lightingEnabled;
    
    if (lightingEnabled) 
    {
        //Access the shader program and set the lighting uniform accordingly
        //Shader& shader = LabEngine::getInstance().shader; // Replace with the actual shader object you are using
        //shader.use();
        //shader.setBool("enableLighting", lightingEnabled);
    }
    else 
    {
       // glDisable(GL_LIGHTING);  // same as above ^^^  :-)
    }
}


void SpecialKeys::readTaskInput(GLFWwindow* m_PixelsGLFWWindow, float deltaT)
{
    F_KeyEntered(m_PixelsGLFWWindow);
    K_KeyEntered(m_PixelsGLFWWindow);
    L_KeyEntered(m_PixelsGLFWWindow);
    M_KeyEntered(m_PixelsGLFWWindow);
    X_KeyEntered(m_PixelsGLFWWindow);
}


/*

void SpecialKeys::readModelInput(GLFWwindow* m_PixelsGLFWWindow, float deltaT, ModelController& modelController)
{
    if (glfwGetKey(m_PixelsGLFWWindow, GLFW_KEY_UP) == GLFW_PRESS)
    {
        modelController.moveModel(ModelController::Direction::FORWARD, deltaT);
    }

    if (glfwGetKey(m_PixelsGLFWWindow, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        modelController.moveModel(ModelController::Direction::BACK, deltaT);
    }

    if (glfwGetKey(m_PixelsGLFWWindow, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        modelController.moveModel(ModelController::Direction::LEFT, deltaT);
    }

    if (glfwGetKey(m_PixelsGLFWWindow, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        modelController.moveModel(ModelController::Direction::RIGHT, deltaT);
    }

    if (glfwGetKey(m_PixelsGLFWWindow, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        modelController.playNextAnimation();
    }
}
        for (MD2_TEST* model : MD2models) {
            if (glfwGetKey(m_window->m_PixelsGLFWWindow, GLFW_KEY_T) == GLFW_PRESS) {
                model->m_position.z -= deltaValue;
            }
            if (glfwGetKey(m_window->m_PixelsGLFWWindow, GLFW_KEY_F) == GLFW_PRESS) {
                model->m_position.x -= deltaValue;
            }
            if (glfwGetKey(m_window->m_PixelsGLFWWindow, GLFW_KEY_G) == GLFW_PRESS) {
                model->m_position.z += deltaValue;
            }
            if (glfwGetKey(m_window->m_PixelsGLFWWindow, GLFW_KEY_H) == GLFW_PRESS) {
                model->m_position.x += deltaValue;
            }
        }
*/

void SpecialKeys::readInput(GLFWwindow* m_PixelsGLFWWindow, float deltaT)
{
    //readModelInput(m_PixelsGLFWWindow, deltaT, modelController);
    readTaskInput(m_PixelsGLFWWindow, deltaT);
}





/*******************



if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
    handleNextAnimation(window);
}
if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
    handleToggleFlying(window);
}
if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
    handleDisplayDemoWindow(window);
}
if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
    handleDisplayGroupPhoto(window);
}
**/