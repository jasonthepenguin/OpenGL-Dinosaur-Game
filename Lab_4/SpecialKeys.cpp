#include "SpecialKeys.h"


SpecialKeys::SpecialKeys() 
{

}


SpecialKeys::~SpecialKeys()
{

}




void SpecialKeys::toggleWireframeMode()
{
    bool wireframe = true;

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
}


void SpecialKeys::displayDemoWindow()
{
    gui->show_demo_window = !gui->show_demo_window;
}


void SpecialKeys::displayGroupPhoto()
{
    gui->show_image = !gui->show_image;
}





void SpecialKeys::readTaskInput(GLFWwindow* m_PixelsGLFWWindow, float deltaT)
{

    if (glfwGetKey(m_PixelsGLFWWindow, GLFW_KEY_K) == GLFW_PRESS)
    {
        toggleWireframeMode();
    }



    if (glfwGetKey(m_PixelsGLFWWindow, GLFW_KEY_F) == GLFW_PRESS)
    {
        triggerFlying();
    }

    if (glfwGetKey(m_PixelsGLFWWindow, GLFW_KEY_M) == GLFW_PRESS)
    {
        displayDemoWindow();
    }

    if (glfwGetKey(m_PixelsGLFWWindow, GLFW_KEY_X) == GLFW_PRESS)
    {
        displayGroupPhoto();
    }
}



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
        playNextAnimation();
    }
}



void SpecialKeys::readInput(GLFWwindow* m_PixelsGLFWWindow, float deltaT, ModelController& modelController, Camera& camera)
{
    readModelInput(m_PixelsGLFWWindow, deltaT, modelController);
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