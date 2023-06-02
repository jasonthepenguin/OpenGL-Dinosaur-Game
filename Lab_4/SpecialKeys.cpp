#include "SpecialKeys.h"

SpecialKeys::SpecialKeys()
{
	auto backCommand = std::make_shared<Back_Command>(*m_MenuManager);
	auto customerSupportCommand = std::make_shared<CustomerSupport_Command>(backCommand, *m_MenuManager);
	auto saveCommand = std::make_shared<Save_Command>(backCommand, std::make_shared<Menu_Manager>(*m_MenuManager));
	auto loadCommand = std::make_shared<Load_Command>(backCommand);
	auto quitCommand = std::make_shared<Quit_Command>(m_PixelsGLFWWindow);


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


void SpecialKeys::Space_KeyEntered(GLFWwindow* m_PixelsGLFWWindow)
{
    auto& engRef = LabEngine::getInstance();
    auto world = engRef.world;

    if (glfwGetKey(m_PixelsGLFWWindow, GLFW_KEY_SPACE) == GLFW_PRESS && !keyStates[GLFW_KEY_SPACE]) {
        // Get camera position and direction
        glm::vec3 camPos = engRef.m_camera->getCameraLocation();
        glm::vec3 camFront = engRef.m_camera->getCameraDirection();
        Vector3 n_position(camPos.x, camPos.y, camPos.z);
        Quaternion orientation = Quaternion::identity();
        Transform transform(n_position, orientation);
        RigidBody* rigidBody = world->createRigidBody(transform);
        BoxShape* boxShape = LabEngine::getInstance().physicsCommon.createBoxShape(Vector3(0.5, 0.5, 0.5));
        Transform r_transform = Transform::identity();
        Collider* collider;
        collider = rigidBody->addCollider(boxShape, r_transform);
        test_cube* newCube = new test_cube();
       // std::unique_ptr<test_cube> newCube = std::make_unique<test_cube>();
        newCube->Init();
        float force = 10.0f;
        rigidBody->setLinearVelocity(Vector3(camFront.x * force, camFront.y * force, camFront.z * force));
        newCube->rigidBody = rigidBody;
        engRef.gameObjects.push_back(newCube);
        keyStates[GLFW_KEY_SPACE] = true;
    }
    else if (glfwGetKey(m_PixelsGLFWWindow, GLFW_KEY_SPACE) == GLFW_RELEASE)
    {
        keyStates[GLFW_KEY_SPACE] = false;
    }
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
    Pause_Menu m_Pause;
    bool paused = false;

    // letters
    F_KeyEntered(m_PixelsGLFWWindow);
    K_KeyEntered(m_PixelsGLFWWindow);
    L_KeyEntered(m_PixelsGLFWWindow);
    M_KeyEntered(m_PixelsGLFWWindow);
    X_KeyEntered(m_PixelsGLFWWindow);

    Space_KeyEntered(m_PixelsGLFWWindow);

    // arrows
    left_KeyEntered(m_PixelsGLFWWindow);
    right_KeyEntered(m_PixelsGLFWWindow);
    up_KeyEntered(m_PixelsGLFWWindow);
    down_KeyEntered(m_PixelsGLFWWindow);

    if (glfwGetKey(m_PixelsGLFWWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        // Check for escape key press
            // Create an instance of Menu_Manager
        Menu_Manager menuManager;

        // Push the Pause_Command to the command stack
        menuManager.pushCommand(std::make_shared<Pause_Command>());

        // Generate the menu
        menuManager.generateMenu();
    }
}




void SpecialKeys::readInput(GLFWwindow* m_PixelsGLFWWindow, float deltaT)
{
    //readModelInput(m_PixelsGLFWWindow, deltaT, modelController);
    readTaskInput(m_PixelsGLFWWindow, deltaT);
}
