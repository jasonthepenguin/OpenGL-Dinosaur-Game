#include "Camera.h"


Camera::Camera(const glm::vec3& initialPosition) : m_Location(initialPosition)
{

    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    float yaw = YAW;
    float pitch = PITCH;


    m_Direction = glm::vec3(0.0f, 0.0f, -1.0f);


    MovementSpeed = SPEED;
    MouseSensitivity = SENSITIVITY;
    Zoom = ZOOM;

    m_Location = initialPosition;
    m_VerticalPlane = up;
    m_CameraYaw = yaw;
    m_CameraPitch = pitch;

    updateCameraVectors();
}


Camera::Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : m_Direction(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    m_Location      = position;
    m_VerticalPlane = up;
    m_CameraYaw     = yaw;
    m_CameraPitch   = pitch;
    updateCameraVectors();
}



Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
{
    m_Location       = glm::vec3(posX, posY, posZ);
    m_VerticalPlane  = glm::vec3(upX, upY, upZ);
    m_CameraYaw      = yaw;
    m_CameraPitch    = pitch;
    updateCameraVectors();
}


Camera::~Camera() {}

// Getters and setters for camera positin, direction, and up vector

glm::vec3 Camera::getCameraLocation()        { return m_Location; }
glm::vec3 Camera::getCameraDirection()       { return m_Direction; }
glm::vec3 Camera::getHorizontalPlane() const { return m_HorizontalPlane; }
glm::vec3 Camera::getVerticalPlane()   const { return m_VerticalPlane; }
float     Camera::getRotationSpeed()   const { return m_RotationSpeed; }
float     Camera::getCameraPitch()     const { return m_CameraPitch; }
float     Camera::getCameraZoom()      const { return m_CameraZoom; }
float     Camera::getCameraYaw()       const { return m_CameraYaw; }
glm::mat4 Camera::GetViewMatrix() { return glm::lookAt(m_Location, m_Location + m_Direction, m_VerticalPlane); }


void Camera::setCameraLocation(const glm::vec3& tempLocation)         { m_Location        = tempLocation;        }
void Camera::setCameraDirection(const glm::vec3& tempDirection)       { m_Direction       = tempDirection;       }
void Camera::setHorizontalPlane(const glm::vec3& tempHorizontalPlane) { m_HorizontalPlane = tempHorizontalPlane; }
void Camera::setVerticalPlane(const glm::vec3& tempVerticalPlane)     { m_VerticalPlane   = tempVerticalPlane;   }
void Camera::setRotationSpeed(float tempRotationSpeed)                { m_RotationSpeed   = tempRotationSpeed;   }
void Camera::setCameraPitch(float tempPitch)                          { m_CameraPitch     = tempPitch;           }
void Camera::setCameraZoom(float tempZoom)                            { m_CameraZoom      = tempZoom;            }
void Camera::setCameraYaw(float tempYaw)                              { m_CameraYaw       = tempYaw;             }



void Camera::readMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;


    m_CameraYaw += xoffset;
    m_CameraPitch += yoffset;


    if (constrainPitch)
    {
        if (m_CameraPitch > 89.0f)
        {
            m_CameraPitch = 89.0f;
        }

        if (m_CameraPitch < -89.0f)
        {
            m_CameraPitch = -89.0f;
        }
    }
    updateCameraVectors();
}


void Camera::updateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(m_CameraYaw)) * cos(glm::radians(m_CameraPitch));
    front.y = sin(glm::radians(m_CameraPitch));
    front.z = sin(glm::radians(m_CameraYaw)) * cos(glm::radians(m_CameraPitch));
    m_Direction = glm::normalize(front);


    m_HorizontalPlane = glm::normalize(glm::cross(m_Direction, m_VerticalPlane));
}