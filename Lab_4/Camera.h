#ifndef CAMERA_H
#define CAMERA_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>


/***************************************************
 * @brief : Camera_Movement
 * @brief : A struct enum to control camera movements
 * @brief : Could potentially change to a struct and use a speed and on keypress to move forward
 ****************************************************/

enum Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};


/***************************************************
  * @brief : Camera const varialbes
  ****************************************************/

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:


    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;


    /********************************************************************************************************
     * @brief : Camera constructor
     * @brief : contains vectors for the camera
     ********************************************************************************************************/

    Camera();


    /********************************************************************************************************
     * @brief : Camera constructor
     * @brief : contains vectors for the camera
     ********************************************************************************************************/

    Camera(const glm::vec3& initialPosition);


    /********************************************************************************************************
     * @brief : Camera constructor
     * @brief : contains vectors for the camera
     ********************************************************************************************************/

    Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch);


    /********************************************************************************************************
     * @brief : Camera constructor
     * @brief : contains scalar values for the camera
     ********************************************************************************************************/

    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);



    /********************************************************************************************************
     * @brief : Camera destructor
     * @brief : used to destroy a camera object
     ********************************************************************************************************/

    ~Camera();



    /************************************************************************************************
     * @brief  getCameraLocation()
     * @brief  Used to get the camera location
     * @return The camera location as a glm::vec3.
     ***********************************************************************************************/

    glm::vec3 getCameraLocation();


    /************************************************************************************************
     * @brief  getCameraDirection()
     * @brief  Used to get the camera direction
     * @return The camera direction as a glm::vec3.
     ***********************************************************************************************/

    glm::vec3 getCameraDirection();


    /************************************************************************************************
     * @brief  getHorizontalPlane()
     * @brief  Used to get the horizontal plane value of the camera
     * @return The horizontal plane as a glm::vec3
     ***********************************************************************************************/

    glm::vec3 getHorizontalPlane() const;


    /************************************************************************************************
     * @brief  getVerticalPlane()
     * @brief  Used to get the VerticalPlane value of the camera
     * @return The vertical plane as a glm::vec3.
     ***********************************************************************************************/

    glm::vec3 getVerticalPlane() const;


    /************************************************************************************************
     * @brief  getRotationSpeed()
     * @brief  Used to get the Rotation Speed of the camera
     * @return The camera rotation speed as a float
     ***********************************************************************************************/

    float getRotationSpeed() const;


    /************************************************************************************************
     * @brief  getCameraPitch()
     * @brief  Used to get the pitch of the camera
     * @return The camera pitch as a float - m_CameraPitch
     ***********************************************************************************************/

    float getCameraPitch() const;


    /************************************************************************************************
     * @brief  getCameraZoom()
     * @brief  Used to get the zoom level of the camera
     * @return The camera zoom as a float m_CameraZoom
     ***********************************************************************************************/

    float getCameraZoom() const;


    /************************************************************************************************
     * @brief  getCameraYaw()
     * @brief  Used to get the camera yaw of the camera
     * @return The camera yaw as a float m_CameraYaw
     ***********************************************************************************************/

    float getCameraYaw() const;


    /************************************************************************************************
     * @brief  getProjectionMatrix()
     * @brief  Used to get the Projection Matrix of the camera
     * @return m_ProjectMatrix as a glm::mat
     ***********************************************************************************************/

    glm::mat4 getProjectionMatrix(float aspectRatio) const;


    /************************************************************************************************
     * @brief  getViewMatrix()
     * @brief  Used to get the view matrix of the camera
     * @return m_ViewMatrix as a glm::mat4.
     ***********************************************************************************************/

    glm::mat4 GetViewMatrix();


    /************************************************************************************************
     * @brief  setCameraLocation()
     * @brief  Used to set the cameras location with a glm::vec3 location
     * @param  tempLocation glm::vec3
     ***********************************************************************************************/

    void setCameraLocation(const glm::vec3& tempLocation);


    /************************************************************************************************
     * @brief setCameraDirection
     * @brief used to Set the camera direction with glm::vec3& direction
     * @param tempDirection The new camera direction as a glm::vec3.
     ************************************************************************************************/

    void setCameraDirection(const glm::vec3& tempDirection);


    /************************************************************************************************
     * @brief setHorizontalPlane
     * @brief used to Set the HorizontalPlane of the camera with glm::vec3& tempHorizontalPlane
     * @param tempHorizontalPlane The new camera value on the horizontalPlane as a glm::vec3.
     ************************************************************************************************/

    void setHorizontalPlane(const glm::vec3& tempHorizontalPlane);


    /************************************************************************************************
     * @brief setVerticalPlane
     * @brief used to Set the Vertical plane value of the camera with glm::vec3& tempVerticalPlane
     * @param tempVerticalPlane The new camera value on the VerticalPlane as a glm::vec3.
     ************************************************************************************************/

    void setVerticalPlane(const glm::vec3& tempVerticalPlane);


    /************************************************************************************************
     * @brief setRotationSpeed
     * @brief used to Set the rotation speed of the camera with float tempRotationSpeed
     * @param tempRotationSpeed The new rotation speed of the camera as a float.
     ************************************************************************************************/

    void setRotationSpeed(float tempRotationSpeed);


    /************************************************************************************************
     * @brief setCameraPitch
     * @brief used to Set the pitch of the camera with float tempPitch
     * @param tempPitch The new camera pitch value as a float
     ************************************************************************************************/

    void setCameraPitch(float tempPitch);


    /************************************************************************************************
     * @brief setCameraZoom
     * @brief used to Set the zoom of the camera with float tempZooom
     * @param tempZooom The new camera zoom value as a float
     ************************************************************************************************/

    void setCameraZoom(float tempZooom);


    /************************************************************************************************
     * @brief setCameraYaw
     * @brief used to Set the yaw of the camera with float tempYaw
     * @param tempYaw The new camera yaw value as a float
     ************************************************************************************************/

    void setCameraYaw(float tempYaw);


    /********************************************************************************************************
     * @brief : GetViewMatrix()
     * @brief : used to get the camera view matrix
     ********************************************************************************************************/

    void readMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);




private:

    float m_CameraYaw;
    float m_CameraPitch;
    float m_CameraZoom;
    float m_RotationSpeed;
    glm::vec3 m_Location;
    glm::vec3 m_Direction;
    glm::vec3 m_VerticalPlane;
    glm::vec3 m_HorizontalPlane;


    /********************************************************************************************************
     * @brief : updateCameraVectors()
     * @brief : used to update the cameras current vector using the updated euler angles
     ********************************************************************************************************/


    void updateCameraVectors();
};
#endif







/*******************************************************************************************************
 * @brief : ProcessKeyboard()
 * @brief : used to process the keyboard inputs by the user
 * @param : direction - CameraMovement
 * @param : deltaTime - float
 ********************************************************************************************************

    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;

    if (direction == FORWARD)

        Position += Front * velocity;

    if (direction == BACKWARD)

        Position -= Front * velocity;

    if (direction == LEFT)

        Position -= Right * velocity;

    if (direction == RIGHT)

        Position += Right * velocity;
}


/*******************************************************************************************************
 * @brief : ProcessMouseMovement()
 * @brief : used to read mouse input from the user
 * @param : constrainPitch - GLboolean
 * @param : xoffset        - float
 * @param : yoffset        - float
 ********************************************************************************************************/

//
//void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
//{
//    xoffset *= MouseSensitivity;
//    yoffset *= MouseSensitivity;
//
//    Yaw += xoffset;
//    Pitch += yoffset;
//
//    // make sure that when pitch is out of bounds, screen doesn't get flipped
//    if (constrainPitch)
//    {
//        if (Pitch > 89.0f)
//
//            Pitch = 89.0f;
//
//        if (Pitch < -89.0f)
//
//            Pitch = -89.0f;
//    }
//
//    // update Front, Right and Up Vectors using the updated Euler angles
//    updateCameraVectors();
//}
//
//
///********************************************************************************************************
// * @brief : ProcessMouseScroll()
// * @brief : used to detemine whether player uses scroll input
// * @param : yOffset - float
// ********************************************************************************************************
//
//
//void ProcessMouseScroll(float yoffset)
//{
//    Zoom -= (float)yoffset;
//
//    if (Zoom < 1.0f)
//
//        Zoom = 1.0f;
//
//    if (Zoom > 45.0f)
//
//        Zoom = 45.0f;
//}
//***/