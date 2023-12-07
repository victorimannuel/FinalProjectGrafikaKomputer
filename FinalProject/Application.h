#pragma once

#include "RenderEngine.h"
#include "Cube.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include <iostream>

class Application :
    public RenderEngine
{
public:
    Application();
    ~Application();
private:
	Shader *shader;
	Texture *cubeDiffTex, *cubeSpecTex, *cubeRedTex, *cubeWhiteTex, *cubeGoldTex, *brickTex, * photoFrameTex, *rockTex, 
		*creepyTex1, * creepyTex2, * creepyTex3, * creepyTex4, * creepyTex5, *creepyTex6, *creepyTex7;
	Cube *cube, *redCube, *whiteCube, *goldCube, *torchCube, *wall, *photoFrame, *rock, *fireCube,
		*creepyPhoto1x, *creepyPhoto2x, *creepyPhoto3x, * creepyPhoto4z, * creepyPhoto5z, *creepyPhoto6x, *creepyPhoto7z;
	Camera *camera;
	float angle = 0;
	glm::vec3 viewPos;
	void setupPerspective();
	void setupCamera();
	void setupLighting();
	void setupTorchLighting();
	virtual void Init();
	virtual void DeInit(); 
	virtual void Update(double deltaTime);
	virtual void Render();
	virtual void ProcessInput(GLFWwindow* window);

	std::vector<glm::vec3> blockPositions;
};

