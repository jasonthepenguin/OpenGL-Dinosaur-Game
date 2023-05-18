#include "SpecialKeys.h"


SpecialKeys::SpecialKeys() 
{

}


SpecialKeys::~SpecialKeys()
{

}


void SpecialKeys::toggleWireframeMode()
{
   // bool wireframe = true;

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



void SpecialKeys::displayDemoWindow()
{
    gui->show_demo_window = !gui->show_demo_window;
}



void SpecialKeys::displayGroupPhoto()
{
    gui->show_image = !gui->show_image;
}



void SpecialKeys::toggleLighting()
{
    bool lightingEnabled = true;

    lightingEnabled = !lightingEnabled;
    
    if (lightingEnabled) 
    {
       // glEnable(GL_LIGHTING);  // these wont work as are deprecated and are from the fixed function pipeline days. Instead should someone have access to a reference to a shader object, 
                                    //and set a uniform for the fragment shader, so it knows not to do any lighting calculations
    }
    else 
    {
       // glDisable(GL_LIGHTING);  // same as above ^^^  :-)
    }
}


void SpecialKeys::readTaskInput(GLFWwindow* m_PixelsGLFWWindow, float deltaT)
{

    // FLYING
    if (glfwGetKey(m_PixelsGLFWWindow, GLFW_KEY_F) == GLFW_PRESS && !keyStates[GLFW_KEY_F])
    {
        triggerFlying();
        keyStates[GLFW_KEY_F] = true;
       // std::cout << "THE F KEY WAS PRESSED!" << std::endl;
    }
    else if (glfwGetKey(m_PixelsGLFWWindow, GLFW_KEY_F) == GLFW_RELEASE)
    {
        keyStates[GLFW_KEY_F] = false;
    }


    // For the K key WIREFRAME
    if (glfwGetKey(m_PixelsGLFWWindow, GLFW_KEY_K) == GLFW_PRESS && !keyStates[GLFW_KEY_K])
    {
        toggleWireframeMode();
        keyStates[GLFW_KEY_K] = true;
    }
    else if (glfwGetKey(m_PixelsGLFWWindow, GLFW_KEY_K) == GLFW_RELEASE)
    {
        keyStates[GLFW_KEY_K] = false;
    }

    // For the L key FOR LIGHTING
    if (glfwGetKey(m_PixelsGLFWWindow, GLFW_KEY_L) == GLFW_PRESS && !keyStates[GLFW_KEY_L])
    {
        toggleLighting();
        keyStates[GLFW_KEY_L] = true;
    }
    else if (glfwGetKey(m_PixelsGLFWWindow, GLFW_KEY_L) == GLFW_RELEASE)
    {
        keyStates[GLFW_KEY_L] = false;
    }

    // For the M key FOR DEMO WINDOW
    if (glfwGetKey(m_PixelsGLFWWindow, GLFW_KEY_M) == GLFW_PRESS && !keyStates[GLFW_KEY_M])
    {
        displayDemoWindow();
        keyStates[GLFW_KEY_M] = true;
    }
    else if (glfwGetKey(m_PixelsGLFWWindow, GLFW_KEY_M) == GLFW_RELEASE)
    {
        keyStates[GLFW_KEY_M] = false;
    }

    // For the X key FOR GROUP PHOTO
    if (glfwGetKey(m_PixelsGLFWWindow, GLFW_KEY_X) == GLFW_PRESS && !keyStates[GLFW_KEY_X])
    {
        displayGroupPhoto();
        keyStates[GLFW_KEY_X] = true;
    }
    else if (glfwGetKey(m_PixelsGLFWWindow, GLFW_KEY_X) == GLFW_RELEASE)
    {
        keyStates[GLFW_KEY_X] = false;
    }
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

*/

//void SpecialKeys::readInput(GLFWwindow* m_PixelsGLFWWindow, float deltaT, ModelController& modelController, Camera& camera)
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