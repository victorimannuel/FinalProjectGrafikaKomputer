#include "Camera.h"

Camera::Camera() {
}

Camera::~Camera() {
}


void Camera::Init(GLFWwindow* window) {
	InitCamera(window);
}

void Camera::Update(double deltaTime) {

}

glm::mat4 Camera::GetViewMatrix() const {
	return glm::lookAt(glm::vec3(posCamX, posCamY, posCamZ), glm::vec3(viewCamX, viewCamY, viewCamZ), glm::vec3(upCamX, upCamY, upCamZ));
}

glm::mat4 Camera::GetProjectionMatrix(float screenWidth, float screenHeight) const {
	return glm::perspective(fovy, screenWidth / screenHeight, 0.1f, 100.0f);
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
//void Camera::ProcessInput(GLFWwindow* window, int screenHeight, int screenWidth) {
// Process all input, including collision detection and response
void Camera::ProcessInput(GLFWwindow* window, int screenHeight, int screenWidth, const std::vector<glm::vec3>& obstacles) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	// zoom camera
	// -----------
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		if (fovy < 90) {
			fovy += 0.0001f;
		}
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		if (fovy > 0) {
			fovy -= 0.0001f;
		}
	}

	// update camera movement 
	// -------------
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		MoveCamera(CAMERA_SPEED);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		MoveCamera(-CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		StrafeCamera(-CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		StrafeCamera(CAMERA_SPEED);
	}

	// update camera rotation
	// ----------------------
	double mouseX, mouseY;
	double midX = screenWidth / 2;
	double midY = screenHeight / 2;
	float angleY = 0.0f;
	float angleZ = 0.0f;

	// Get mouse position
	glfwGetCursorPos(window, &mouseX, &mouseY);
	if ((mouseX == midX) && (mouseY == midY)) {
		return;
	}

	// Set mouse position
	glfwSetCursorPos(window, midX, midY);

	// Get the direction from the mouse cursor, set a resonable maneuvering speed
	angleY = (float)((midX - mouseX)) / 1000;
	angleZ = (float)((midY - mouseY)) / 1000;

	// The higher the value is the faster the camera looks around.
	viewCamY += angleZ * 2;

	// limit the rotation around the x-axis
	if ((viewCamY - posCamY) > 8) {
		viewCamY = posCamY + 8;
	}
	if ((viewCamY - posCamY) < -8) {
		viewCamY = posCamY - 8;
	}
	RotateCamera(-angleY);

	// Process camera movement
	ProcessCameraMovement(window, screenHeight, screenWidth, obstacles);

}

void Camera::InitCamera(GLFWwindow* window)
{
	posCamX = 0.0f;
	posCamY = 1.0f;
	posCamZ = 8.0f;
	viewCamX = 0.0f;
	viewCamY = 1.0f;
	viewCamZ = 0.0f;
	upCamX = 0.0f;
	upCamY = 1.0f;
	upCamZ = 0.0f;
	//CAMERA_SPEED = 0.0002f;
	CAMERA_SPEED = 0.002f;
	fovy = 45.0f;
	cameraDirection = glm::vec3(0.0f, 0.0f, -1.0f);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}


void Camera::MoveCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	// forward positive cameraspeed and backward negative -cameraspeed.
	posCamX = posCamX + x * speed;
	posCamZ = posCamZ + z * speed;
	viewCamX = viewCamX + x * speed;
	viewCamZ = viewCamZ + z * speed;
}

void Camera::StrafeCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	float orthoX = -z;
	float orthoZ = x;

	// left positive cameraspeed and right negative -cameraspeed.
	posCamX = posCamX + orthoX * speed;
	posCamZ = posCamZ + orthoZ * speed;
	viewCamX = viewCamX + orthoX * speed;
	viewCamZ = viewCamZ + orthoZ * speed;
}

void Camera::RotateCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	viewCamZ = (float)(posCamZ + glm::sin(speed) * x + glm::cos(speed) * z);
	viewCamX = (float)(posCamX + glm::cos(speed) * x - glm::sin(speed) * z);
}

// Update the ProcessCameraMovement function
void Camera::ProcessCameraMovement(GLFWwindow* window, int screenHeight, int screenWidth, const std::vector<glm::vec3>& obstacles) {
	// Calculate the new camera position based on user input
	glm::vec3 newPosition = glm::vec3(viewCamX, viewCamY, viewCamZ) + (CAMERA_SPEED * cameraDirection);
	float OBSTACLE_SIZE = 0.1f;
	for (const glm::vec3& obstacle : obstacles) {
		std::cout << "OBSTACLES" << std::endl;
		if (CheckCollision(newPosition, obstacle, OBSTACLE_SIZE)) {
			// Calculate the collision normal (the vector pointing out of the obstacle)
			glm::vec3 collisionNormal = glm::normalize(newPosition - obstacle);

			/*std::cout << "TESTTTTT COLLISION" << std::endl;*/
			// Reflect the camera direction off the collision normal
			cameraDirection = glm::reflect(cameraDirection, collisionNormal);

			// Adjust the new position to slide along the wall
			newPosition = glm::vec3(viewCamX, viewCamY, viewCamZ) + (CAMERA_SPEED * cameraDirection);

			std::cout << "Collision detected with obstacle at (" << obstacle.x << ", " << obstacle.y << ", " << obstacle.z << ")" << std::endl;

		}
	}

	// Update the camera position
	viewCamX = newPosition.x;
	viewCamY = newPosition.y;
	viewCamZ = newPosition.z;
}

// Update the collision check function
bool Camera::CheckCollision(const glm::vec3& cameraPos, const glm::vec3& obstaclePos, float obstacleSize) {
	float cameraRadius = 0.2f;
	// Calculate the distance between the camera and the obstacle
	float distance = glm::distance(cameraPos, obstaclePos);

	// Calculate the sum of radii for collision (camera and obstacle)
	float collisionDistance = cameraRadius + obstacleSize / 2.0f;

	// Check if a collision occurs
	if (distance < collisionDistance) {
		return true; // Collision detected
	}

	return false; // No collision
}