#pragma once

#include "RenderEngine.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <SOIL/SOIL.h>

#include <vector>
#include <GLFW/glfw3.h>

class Camera
{
public:
	Camera();
	~Camera();
	void Init(GLFWwindow* window);
	void Update(double deltaTime);
	void ProcessInput(GLFWwindow* window, int screenHeight, int screenWidth, const std::vector<glm::vec3>& obstacles);

	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjectionMatrix(float screenWidth, float screenHeight) const;
private:
	GLuint shaderProgram, VBO, VAO, EBO, texture, VBO2, VAO2, EBO2, texture2;
	float viewCamX, viewCamY, viewCamZ, upCamX, upCamY, upCamZ, posCamX, posCamY, posCamZ, CAMERA_SPEED, fovy;
	int screenHeight, screenWidth;
	void MoveCamera(float speed);
	void StrafeCamera(float speed);
	void RotateCamera(float speed);
	void InitCamera(GLFWwindow* window);

	glm::vec3 cameraDirection;

	void ProcessCameraMovement(GLFWwindow* window, int screenHeight, int screenWidth, const std::vector<glm::vec3>& obstacles);
	bool CheckCollision(const glm::vec3& cameraPos, const glm::vec3& obstaclePos, float obstacleSize);

};

