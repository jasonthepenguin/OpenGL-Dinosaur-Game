#include "Camera.h"


Camera::Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : m_Direction(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}



Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
{
    Position = glm::vec3(posX, posY, posZ);
    WorldUp = glm::vec3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}


Camera::~Camera() {}

// Getters and setters for camera positin, direction, and up vector

glm::vec3 Camera::getCameraLocation()        { return m_Location;        }
glm::vec3 Camera::getCameraDirection()       { return m_Direction;       }
glm::vec3 Camera::getHorizontalPlane() const { return m_HorizontalPlane; }
glm::vec3 Camera::getVerticalPlane()   const { return m_VerticalPlane;   }
float     Camera::getRotationSpeed()   const { return m_RotationSpeed;   }
float     Camera::getCameraPitch()     const { return m_CameraPitch;     }  
float     Camera::getCameraZoom()      const { return m_CameraZoom;      }
float     Camera::getCameraYaw()       const { return m_CameraYaw;       }
glm::mat4 Camera::GetViewMatrix()            { return glm::lookAt(m_Location, m_Location + m_Direction, m_VerticalPlane); }


void Camera::setCameraLocation(const glm::vec3& tempLocation)         { m_Location        = tempLocation;        }
void Camera::setCameraDirection(const glm::vec3& tempDirection)       { m_Direction       = tempDirection;       }
void Camera::setHorizontalPlane(const glm::vec3& tempHorizontalPlane) { m_HorizontalPlane = tempHorizontalPlane; }
void Camera::setVerticalPlane(const glm::vec3& tempVerticalPlane)     { m_VerticalPlane   = tempVerticalPlane;   }
void Camera::setRotationSpeed(float tempRotationSpeed)                { m_RotationSpeed   = tempRotationSpeed;   }
void Camera::setCameraPitch(float tempPitch)                          { m_CameraPitch     = tempPitch;           }
void Camera::setCameraZoom(float tempZoom)                            { m_CameraZoom      = tempZoom;            }
void Camera::setCameraYaw(float tempYaw)                              { m_CameraYaw       = tempYaw;             }