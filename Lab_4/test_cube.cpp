#include "test_cube.h"

void test_cube::Init()
{
	initPhysics();
	init();
}


void test_cube::initPhysics()
{

	auto world = LabEngine::getInstance().world;
	Vector3 n_position(position.x, position.y, position.z);
	Quaternion orientation = Quaternion::identity();
	Transform transform(n_position, orientation);

	rigidBody = world->createRigidBody(transform);
	BoxShape* boxShape = LabEngine::getInstance().physicsCommon.createBoxShape(Vector3(0.5, 0.5, 0.5));

	// Relative transform
	Transform r_transform = Transform::identity();
	// Add the collider to the rigidbody
	Collider* collider;
	
	collider = rigidBody->addCollider(boxShape, r_transform);
	ourCollider = collider;
}


void test_cube::Update(float deltaTime)
{
	//Gettheupdatedpositionofthebody
	const Transform& transform = rigidBody->getTransform();
	const Vector3& n_position = transform.getPosition();

	position.x = n_position.x;
	position.y = n_position.y;
	position.z = n_position.z;


	// update position of our labPhysics AABB
	if (boundingBox != nullptr)
	{
		boundingBox->updateAABBPosition(position);
	}


	// attempting to get rotations working when collding with the terrain (include quats in our headers )
	auto quat = transform.getOrientation();
	glm::quat boxQuat(quat.x, quat.y, quat.z, quat.w);
	glm::mat3 rotationMatrix = glm::mat3_cast(boxQuat);
	glm::mat4 n_rotationMatrix4x4(rotationMatrix);
	rotationMatrix4x4 = n_rotationMatrix4x4;

}


void test_cube::Render(Shader& shader, const glm::mat4& view, const glm::mat4& projection)
{
	// render the object and pass the shader?
	draw(shader);
}


test_cube::~test_cube()
{
	auto world = LabEngine::getInstance().world;
	world->destroyRigidBody(rigidBody);
	delete ourCollider;

	// freeing opengl resources
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
}


void test_cube::collisionEvent(GameObject* gameObj) 
{
	//std::cout << "Box Class dealing with a collision event" << std::endl;
}