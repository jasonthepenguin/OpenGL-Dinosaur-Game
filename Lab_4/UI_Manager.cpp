#include "UI_Manager.h"
#include "Keyboard_Input.h"
#include "Mouse_Input.h"

UI_Manager::UI_Manager() 
{
    m_PlayerKeyboard = nullptr;
    m_PlayerMouse = nullptr;

}

UI_Manager::~UI_Manager(){}


void UI_Manager::setPlayerKeyboard(std::shared_ptr<Keyboard_Input> keyboard) { m_PlayerKeyboard = keyboard; }
void UI_Manager::setPlayerMouse(std::shared_ptr<Mouse_Input> mouse)		     { m_PlayerMouse    = mouse;    }



void UI_Manager::readUserInput(GLFWwindow* m_PixelsGLFWWindow, float deltaT)
{
    if (m_PlayerKeyboard)
    {
        m_PlayerKeyboard->readInput(m_PixelsGLFWWindow, deltaT);
    }


    if (m_PlayerMouse)
    {
        m_PlayerMouse->readInput(m_PixelsGLFWWindow, deltaT);
    }
}