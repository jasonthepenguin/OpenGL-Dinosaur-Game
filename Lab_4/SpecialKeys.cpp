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
        if (action != nullptr) {
            (this->*action)();
        }

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

void SpecialKeys::U_KeyEntered(GLFWwindow* m_PixelsGLFWWindow)
{
    handleKeyEntered(m_PixelsGLFWWindow, GLFW_KEY_U, keyStates[GLFW_KEY_U], &SpecialKeys::toggleMouseAction);
}


void SpecialKeys::Space_KeyEntered(GLFWwindow* m_PixelsGLFWWindow)
{
    auto& engRef = LabEngine::getInstance();
    auto world = engRef.world;

    if (glfwGetKey(m_PixelsGLFWWindow, GLFW_KEY_SPACE) == GLFW_PRESS && !keyStates[GLFW_KEY_SPACE]) {
        // Get camera position and direction
        glm::vec3 camPos = engRef.m_camera->getCameraLocation();
        glm::vec3 camFront = engRef.m_camera->getCameraDirection();

        // Create a rigid body in the world
        Vector3 n_position(camPos.x, camPos.y, camPos.z);
        Quaternion orientation = Quaternion::identity();
        Transform transform(n_position, orientation);

        RigidBody* rigidBody = world->createRigidBody(transform);
       
 

        // Create a box collision shape
        BoxShape* boxShape = LabEngine::getInstance().physicsCommon.createBoxShape(Vector3(0.5, 0.5, 0.5));

        // Relative transform
        Transform r_transform = Transform::identity();

        // Add the collider to the rigidbody
        Collider* collider;
        collider = rigidBody->addCollider(boxShape, r_transform);

        

        test_cube* newCube = new test_cube();
       // std::unique_ptr<test_cube> newCube = std::make_unique<test_cube>();
        newCube->Init();
        float force = 20.0f;

        // Set the initial linear velocity based on camera direction
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

void SpecialKeys::toggleMouseAction()
{
    LabEngine::getInstance().m_window->toggleMouse();
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
   // gui->show_demo_window = !gui->show_demo_window;

    gui->showPauseMenu = !gui->showPauseMenu;
    LabEngine::getInstance().m_window->toggleMouse();
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
    U_KeyEntered(m_PixelsGLFWWindow);

    Space_KeyEntered(m_PixelsGLFWWindow);

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
