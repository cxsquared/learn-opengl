#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
		: Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		Position = position;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
	: Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	Position = glm::vec3(posX, posY, posZ);
	WorldUp = glm::vec3(upX, upY, upZ);
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(Position, Position + LookAt, Up);
	//return this->lookAt(Position, Position + LookAt, Up);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	glm::vec3 movementFront = this->getMovementFront();

	float velocity = MovementSpeed * deltaTime;
	if (direction == FORWARD)
		Position += movementFront * velocity;
	if (direction == BACKWARD)
		Position -= movementFront * velocity;
	if (direction == LEFT)
		Position -= Right * velocity;
	if (direction == RIGHT )
		Position += Right * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	if (constrainPitch) {
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}
	
	updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
	if (Zoom >= 1.0f && Zoom <= 45.0f)
		Zoom -= yoffset;
	if (Zoom <= 1.0f)
		Zoom = 1.0f;
	if (Zoom >= 90.0f)
		Zoom = 90.0f;
}

void Camera::updateCameraVectors()
{
	glm::vec3 lookAt;
	lookAt.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	lookAt.y = sin(glm::radians(Pitch));
	lookAt.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	LookAt = glm::normalize(lookAt);

	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(0.0f));
	front.y = sin(glm::radians(0.0f));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(0.0f));
	Front = glm::normalize(front);

	if (Flying)
	{
		Right = glm::normalize(glm::cross(LookAt, WorldUp));
		Up = glm::normalize(glm::cross(Right, LookAt));
	}
	else
	{
		Right = glm::normalize(glm::cross(Front, WorldUp));
		Up = glm::normalize(glm::cross(Right, Front));
	}
}

glm::vec3 Camera::getMovementFront()
{
	return Flying ? LookAt : Front;
}

glm::mat4 Camera::lookAt(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp)
{
	// 1. Position
	// 2. Direction
	glm::vec3 zaxis = glm::normalize(position - target);
	// 3. Positive Right vector
	glm::vec3 xaxis = glm::normalize(glm::cross(glm::normalize(worldUp), zaxis));
	// 4. Up vector
	glm::vec3 yaxis = glm::cross(zaxis, xaxis);

	// Create transation and rotation matix
	// mat[col][row]
	glm::mat4 translation, rotation;
	translation[3][0] = -position.x;
	translation[3][1] = -position.y;
	translation[3][2] = -position.z;
	rotation[0][0] = xaxis.x;
	rotation[1][0] = xaxis.y;
	rotation[2][0] = xaxis.z;
	rotation[0][1] = yaxis.x;
	rotation[1][1] = yaxis.y;
	rotation[2][1] = yaxis.z;
	rotation[0][2] = zaxis.x;
	rotation[1][2] = zaxis.y;
	rotation[2][2] = zaxis.z;

	return rotation * translation; // read right to left
}