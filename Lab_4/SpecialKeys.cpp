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

// ARROWS
void SpecialKeys::left_KeyEntered(GLFWwindow* m_PixelsGLFWWindow)
{
   // handleKeyEntered(m_PixelsGLFWWindow, GLFW_KEY_LEFT, keyStates[GLFW_KEY_LEFT], nullptr);
}

void SpecialKeys::right_KeyEntered(GLFWwindow* m_PixelsGLFWWindow)
{

    auto& engRef = LabEngine::getInstance();

   
    if (glfwGetKey(m_PixelsGLFWWindow, GLFW_KEY_RIGHT) == GLFW_PRESS && !keyStates[GLFW_KEY_RIGHT])
    {
       // (this->*action)();
        for (auto model : engRef.MD2models)
        {
            model->playNextAnimation();
        }
        keyStates[GLFW_KEY_RIGHT] = true;
    }
    else if (glfwGetKey(m_PixelsGLFWWindow, GLFW_KEY_RIGHT) == GLFW_RELEASE)
    {
        keyStates[GLFW_KEY_RIGHT] = false;
    }

}

void SpecialKeys::up_KeyEntered(GLFWwindow* m_PixelsGLFWWindow)
{
   // handleKeyEntered(m_PixelsGLFWWindow, GLFW_KEY_UP, keyStates[GLFW_KEY_UP], nullptr);

}

void SpecialKeys::down_KeyEntered(GLFWwindow* m_PixelsGLFWWindow)
{
   // handleKeyEntered(m_PixelsGLFWWindow, GLFW_KEY_DOWN, keyStates[GLFW_KEY_DOWN], nullptr);

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

    }
    else 
    {
       // glDisable(GL_LIGHTING);  // same as above ^^^  :-)
    }
}


void SpecialKeys::readTaskInput(GLFWwindow* m_PixelsGLFWWindow, float deltaT)
{
    // letters
    F_KeyEntered(m_PixelsGLFWWindow);
    K_KeyEntered(m_PixelsGLFWWindow);
    L_KeyEntered(m_PixelsGLFWWindow);
    M_KeyEntered(m_PixelsGLFWWindow);
    X_KeyEntered(m_PixelsGLFWWindow);

    // arrows
    left_KeyEntered(m_PixelsGLFWWindow);
    right_KeyEntered(m_PixelsGLFWWindow);
    up_KeyEntered(m_PixelsGLFWWindow);
    down_KeyEntered(m_PixelsGLFWWindow);


    if (glfwGetKey(m_PixelsGLFWWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(m_PixelsGLFWWindow, true);
    }
}




void SpecialKeys::readInput(GLFWwindow* m_PixelsGLFWWindow, float deltaT)
{
    //readModelInput(m_PixelsGLFWWindow, deltaT, modelController);
    readTaskInput(m_PixelsGLFWWindow, deltaT);
}
