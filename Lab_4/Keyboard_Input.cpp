#include "Keyboard_Input.h"




Keyboard_Input::Keyboard_Input(std::shared_ptr<Camera> playerCamera) :
    m_SpecialKeys(std::make_shared<SpecialKeys>()),
    m_MovementKeys(std::make_shared<MovementKeys>())
{
    // Initialize other members here if needed
}


void Keyboard_Input::readInput(GLFWwindow* m_PixelsGLFWWindow, float deltaT)
{
    if (m_SpecialKeys)
    {
        m_SpecialKeys->readInput(m_PixelsGLFWWindow, deltaT);
    }

    if (m_MovementKeys)
    {
        m_MovementKeys->readInput(m_PixelsGLFWWindow, deltaT);
    }
}