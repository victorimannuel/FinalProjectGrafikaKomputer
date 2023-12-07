#include "Application.h"

Application::Application()
{

}

Application::~Application()
{
}

void Application::setupPerspective()
{
	// Pass perspective projection matrix
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)this->screenWidth / (GLfloat)this->screenHeight, 0.1f, 100.0f);
	shader->setMat4("projection", projection);
}

void Application::setupCamera()
{
	// LookAt camera (position, target/direction, up)
	viewPos = glm::vec3(0, 1, 5);
	glm::mat4 view = glm::lookAt(viewPos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	shader->setMat4("view", view);
}

void Application::setupLighting()
{
	// Set lighting attributes
	glm::vec3 lightPos = glm::vec3(0, 1, 0);
	shader->setVec3("lightPos", lightPos);
	shader->setVec3("viewPos", viewPos);
	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	shader->setVec3("lightColor", lightColor);
}

void Application::setupTorchLighting()
{
	// Set lighting attributes
	glm::vec3 lightPos = glm::vec3(15, 5, 2);
	shader->setVec3("lightPos", lightPos);
	shader->setVec3("viewPos", viewPos);
	//glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 lightColor = glm::vec3(209.0f / 255, 121.0f / 255, 86.0f / 255);
	shader->setVec3("lightColor", lightColor);
}

void Application::Init()
{

	// Build a lighting map shader
	shader = new Shader("texturedCube.vert", "texturedCube.frag");
	shader->Init();
	// Create cube diffuse texture and specular texture
	cubeDiffTex = new Texture("crate_diffusemap.png");
	cubeDiffTex->Init();
	cubeSpecTex = new Texture("crate_specularmap.png");
	cubeSpecTex->Init();
	cubeRedTex = new Texture("red_texture.png");
	cubeRedTex->Init();
	cubeWhiteTex = new Texture("white_texture.png");
	cubeWhiteTex->Init();
	cubeGoldTex = new Texture("gold_texture.png");
	cubeGoldTex->Init();
	brickTex = new Texture("mario_brick_texture.png");
	brickTex->Init();
	photoFrameTex = new Texture("horror_texture.png");
	photoFrameTex->Init();
	rockTex = new Texture("grey_rock_texture.png");
	rockTex->Init();
	creepyTex1 = new Texture("creepy1.png");
	creepyTex1->Init();
	creepyTex2 = new Texture("creepy2.png");
	creepyTex2->Init();
	creepyTex3 = new Texture("creepy3.png");
	creepyTex3->Init();
	creepyTex4 = new Texture("creepy4.png");
	creepyTex4->Init();
	creepyTex5 = new Texture("creepy5.png");
	creepyTex5->Init();
	creepyTex6 = new Texture("creepy6.png");
	creepyTex6->Init();
	creepyTex7 = new Texture("creepy7.png");
	creepyTex6->Init();

	// Create instance of cube
	cube = new Cube(shader, cubeDiffTex, cubeSpecTex);
	cube->Init();
	cube->SetScale(0.2f, 0.2f, 0.2f);

	// Red Cube
	redCube = new Cube(shader, cubeRedTex, cubeSpecTex);
	redCube->Init();
	redCube->SetScale(0.2f, 0.2f, 0.2f);

	// White Cube
	whiteCube = new Cube(shader, cubeWhiteTex, cubeSpecTex);
	whiteCube->Init();
	whiteCube->SetScale(0.2f, 0.2f, 0.2f);

	// Gold Cube
	goldCube = new Cube(shader, cubeGoldTex, cubeSpecTex);
	goldCube->Init();
	goldCube->SetScale(0.2f, 0.2f, 0.2f);

	// Torch cube
	torchCube = new Cube(shader, cubeDiffTex, cubeSpecTex);
	torchCube->Init();
	//torchCube->SetScale(0.1f, 0.5f, 0.1f);
	torchCube->SetScale(0.2f, 0.2f, 0.2f);

	// Fire cube
	fireCube = new Cube(shader, cubeRedTex, cubeSpecTex);
	fireCube->Init();
	fireCube->SetScale(0.2f, 0.2f, 0.2f);

	// Wall
	wall = new Cube(shader, brickTex, cubeSpecTex);
	wall->Init();
	wall->SetScale(0.2f, 0.2f, 0.2f);

	// Creepy Photo 1
	creepyPhoto1x = new Cube(shader, creepyTex1, cubeSpecTex);
	creepyPhoto1x->Init();
	creepyPhoto1x->SetScale(1.0f, 1.0f, 0.05f);
	// Creepy Photo 2
	creepyPhoto2x = new Cube(shader, creepyTex2, cubeSpecTex);
	creepyPhoto2x->Init();
	creepyPhoto2x->SetScale(1.0f, 1.0f, 0.05f);
	// Creepy Photo 3
	creepyPhoto3x = new Cube(shader, creepyTex3, cubeSpecTex);
	creepyPhoto3x->Init();
	creepyPhoto3x->SetScale(1.0f, 1.0f, 0.05f);
	// Creepy Photo 4
	creepyPhoto4z = new Cube(shader, creepyTex4, cubeSpecTex);
	creepyPhoto4z->Init();
	creepyPhoto4z->SetScale(0.05f, 1.0f, 1.0f);
	// Creepy Photo 5
	creepyPhoto5z = new Cube(shader, creepyTex5, cubeSpecTex);
	creepyPhoto5z->Init();
	creepyPhoto5z->SetScale(0.05f, 1.0f, 1.0f);
	// Creepy Photo 6
	creepyPhoto6x = new Cube(shader, creepyTex6, cubeSpecTex);
	creepyPhoto6x->Init();
	creepyPhoto6x->SetScale(1.0f, 1.0f, 0.05f);
	// Creepy Photo 7
	creepyPhoto7z = new Cube(shader, creepyTex7, cubeSpecTex);
	creepyPhoto7z->Init();
	creepyPhoto7z->SetScale(0.05f, 1.0f, 1.0f);

	// Photo Frame
	photoFrame = new Cube(shader, photoFrameTex, cubeSpecTex);
	photoFrame->Init();
	photoFrame->SetScale(0.1f, 0.1f, 0.1f);

	// Rock
	rock = new Cube(shader, rockTex, cubeSpecTex);
	rock->Init();
	rock->SetScale(0.2f, 0.2f, 0.2f);
	
	// Setup perspective 
	setupPerspective();
	// Setup camera
	setupCamera();
	// Setup lighting
	//setupLighting();
	setupTorchLighting();

	camera = new Camera();
	camera->Init(window);
}

void Application::DeInit()
{
	delete cube;
}

void Application::Update(double deltaTime)
{
	angle += (float)((deltaTime * 1.5f) / 1000);

	cube->SetRotation(angle, 0, 1, 0);
	redCube->SetRotation(angle, 0, 1, 0);
	whiteCube->SetRotation(angle, 0, 1, 0);
	goldCube->SetRotation(angle, 0, 1, 0);
	torchCube->SetRotation(0, 0, 1, 0);
	fireCube->SetRotation(angle, 1, 0, 0);
	wall->SetRotation(0, 0, 1, 0);
	photoFrame->SetRotation(0, 0, 1, 0);
	rock->SetRotation(0, 0, 1, 0);
	creepyPhoto1x->SetRotation(-90 * 1.5f/1000, 0, 0, 1);
	creepyPhoto2x->SetRotation(-60 * 1.5f / 1000, 0, 0, 1);
	creepyPhoto3x->SetRotation(90 * 1.5f / 1000, 0, 0, 1);
	creepyPhoto4z->SetRotation(60 * 1.5f / 1000, 0, 0, 1);
	creepyPhoto5z->SetRotation(-90 * 1.5f / 1000, 0, 0, 1);
	creepyPhoto6x->SetRotation(30 * 1.5f / 1000, 0, 0, 1);
	creepyPhoto7z->SetRotation(-30 * 1.5f / 1000, 0, 0, 1);

	// Camera
	camera->Update(deltaTime);
}

void Application::Render()
{
	glViewport(0, 0, this->screenWidth, this->screenHeight);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_DEPTH_TEST);

	// Camera
	shader->setMat4("view", camera->GetViewMatrix());
	shader->setMat4("projection", camera->GetProjectionMatrix(this->screenWidth, this->screenHeight));

	// Wall
	// Surround wall back
	for (int x = 0; x <= 50; x++) {
		if (x < 30 || x > 35) {
			for (int y = 0; y < 10; y++) {
				wall->SetPosition(x, y, -50); wall->Draw();
			}
		}
	}
	// Surround wall left
	for (int z = 0; z >= -50; z--) {
		for (int y = 0; y < 10; y++) {
			wall->SetPosition(0, y, z); wall->Draw();
		}
	}
	// Surround wall right
	for (int z = 0; z >= -50; z--) {
		for (int y = 0; y < 10; y++) {
			wall->SetPosition(50, y, z); wall->Draw();
		}
	}
	// Surround wall front
	for (int x = 10; x <= 50; x++) {
		for (int y = 0; y < 10; y++) {
			wall->SetPosition(x, y, 0); wall->Draw();
		}
	}
	// Top 
	for (int x = 0; x <= 50; x++) {
		for (int z = 0; z >= -50; z--) {
			wall->SetPosition(x, 10, z); wall->Draw();
		}
	}
	// Floor 
	for (int x = 0; x <= 50; x++) {
		for (int z = 0; z >= -50; z--) {
			wall->SetPosition(x, -1, z); wall->Draw();
		}
	}
	// Wall inside
	for (int x = 0; x <= 10; x++) {
		for (int y = 0; y < 10; y++) {
			wall->SetPosition(x, y, -10); wall->Draw();
		}
	}
	for (int z = 0; z >= -20; z--) {
		for (int y = 0; y < 10; y++) {
			wall->SetPosition(20, y, z); wall->Draw();
		}
	}
	for (int x = 10; x <= 30; x++) {
		for (int y = 0; y < 10; y++) {
			wall->SetPosition(x, y, -30); wall->Draw();
		}
	}
	for (int z = -10; z >= -20; z--) {
		for (int y = 0; y < 10; y++) {
			wall->SetPosition(10, y, z); wall->Draw();
		}
	}
	for (int z = -10; z >= -30; z--) {
		for (int y = 0; y < 10; y++) {
			wall->SetPosition(30, y, z); wall->Draw();
		}
	}
	for (int x = 30; x <= 40; x++) {
		for (int y = 0; y < 10; y++) {
			wall->SetPosition(x, y, -10); wall->Draw();
		}
	}
	for (int z = 0; z >= -10; z--) {
		for (int y = 0; y < 10; y++) {
			wall->SetPosition(40, y, z); wall->Draw();
		}
	}
	for (int x = 0; x <= 40; x++) {
		if (x < 10 || x > 15) {
			for (int y = 0; y < 10; y++) {
				wall->SetPosition(x, y, -40); wall->Draw();
			}
		}
	}
	for (int z = -40; z >= -50; z--) {
		for (int y = 0; y < 10; y++) {
			wall->SetPosition(30, y, z); wall->Draw();
		}
	}
	for (int z = -20; z >= -40; z--) {
		for (int y = 0; y < 10; y++) {
			wall->SetPosition(40, y, z); wall->Draw();
		}
	}
	// End of wall inside

	// Photo
	creepyPhoto1x->SetPosition(45/5, 1, -49.5*4);
	creepyPhoto1x->Draw();
	creepyPhoto2x->SetPosition(5/5, 1, -10.5 * 4);
	creepyPhoto2x->Draw();
	creepyPhoto3x->SetPosition(35 / 5, 1, -10.5 * 4);
	creepyPhoto3x->Draw();
	creepyPhoto4z->SetPosition(0.5 * 4, 1, -45 / 5);
	creepyPhoto4z->Draw();
	creepyPhoto5z->SetPosition(39.5 * 4, 1, -35 / 5);
	creepyPhoto5z->Draw();
	creepyPhoto6x->SetPosition(15/5, 1, -29.5 * 4);
	creepyPhoto6x->Draw();
	creepyPhoto7z->SetPosition(39.5 * 4, 1, -5 / 5);
	creepyPhoto7z->Draw();
	
	// X Cube Coin
	// Layer 1
	goldCube->SetPosition(0 + 25, 1, 0 + -5);
	goldCube->Draw();
	// Layer 2
	goldCube->SetPosition(-0.5 + 25, 1.5, -5);
	goldCube->Draw();
	goldCube->SetPosition(0.5 + 25, 1.5, -5);
	goldCube->Draw();
	// Layer 3
	goldCube->SetPosition(-1 + 25, 2, -5);
	goldCube->Draw();
	goldCube->SetPosition(-0 + 25, 2, -5);
	goldCube->Draw();
	goldCube->SetPosition(1 + 25, 2, -5);
	goldCube->Draw();
	// Layer 4
	goldCube->SetPosition(-0.5 + 25, 2.5, -5);
	goldCube->Draw();
	goldCube->SetPosition(0.5 + 25, 2.5, -5);
	goldCube->Draw();
	// Layer 5
	goldCube->SetPosition(0 + 25, 3, -5);
	goldCube->Draw();

	// X Cube Coin
	// Layer 1
	goldCube->SetPosition(0 + 45, 1, 0 + -5);
	goldCube->Draw();
	// Layer 2
	goldCube->SetPosition(-0.5 + 45, 1.5, -5);
	goldCube->Draw();
	goldCube->SetPosition(0.5 + 45, 1.5, -5);
	goldCube->Draw();
	// Layer 3
	goldCube->SetPosition(-1 + 45, 2, -5);
	goldCube->Draw();
	goldCube->SetPosition(-0 + 45, 2, -5);
	goldCube->Draw();
	goldCube->SetPosition(1 + 45, 2, -5);
	goldCube->Draw();
	// Layer 4
	goldCube->SetPosition(-0.5 + 45, 2.5, -5);
	goldCube->Draw();
	goldCube->SetPosition(0.5 + 45, 2.5, -5);
	goldCube->Draw();
	// Layer 5
	goldCube->SetPosition(0 + 45, 3, -5);
	goldCube->Draw();

	// Z Cube Coin
	// Layer 1
	goldCube->SetPosition(0 + 25, 1, 0 + -45);
	goldCube->Draw();
	// Layer 2
	goldCube->SetPosition(0 + 25, 1.5, -0.5 + -45);
	goldCube->Draw();
	goldCube->SetPosition(0 + 25, 1.5, 0.5 + -45);
	goldCube->Draw();
	// Layer 3
	goldCube->SetPosition(0 + 25, 2, -1 + -45);
	goldCube->Draw();
	goldCube->SetPosition(0 + 25, 2, 0 + -45);
	goldCube->Draw();
	goldCube->SetPosition(0 + 25, 2, 1 + -45);
	goldCube->Draw();
	// Layer 4
	goldCube->SetPosition(0 + 25, 2.5, -0.5 + -45);
	goldCube->Draw();
	goldCube->SetPosition(0 + 25, 2.5, 0.5 + -45);
	goldCube->Draw();
	// Layer 5
	goldCube->SetPosition(0 + 25, 3, 0 + -45);
	goldCube->Draw();

	// X Cube Coin
	// Layer 1
	goldCube->SetPosition(0 + 33, 1, 0 + -58);
	goldCube->Draw();
	// Layer 2
	goldCube->SetPosition(-0.5 + 33, 1.5, -58);
	goldCube->Draw();
	goldCube->SetPosition(0.5 + 33, 1.5, -58);
	goldCube->Draw();
	// Layer 3
	goldCube->SetPosition(-1 + 33, 2, -58);
	goldCube->Draw();
	goldCube->SetPosition(-0 + 33, 2, -58);
	goldCube->Draw();
	goldCube->SetPosition(1 + 33, 2, -58);
	goldCube->Draw();
	// Layer 4
	goldCube->SetPosition(-0.5 + 33, 2.5, -58);
	goldCube->Draw();
	goldCube->SetPosition(0.5 + 33, 2.5, -58);
	goldCube->Draw();
	// Layer 5
	goldCube->SetPosition(0 + 33, 3, -58);
	goldCube->Draw();
	// End of cube coin

	// X Cube Coin
	// Layer 1
	goldCube->SetPosition(0 + 30, 1, 0 + -58);
	goldCube->Draw();
	// Layer 2
	goldCube->SetPosition(-0.5 + 30, 1.5, -58);
	goldCube->Draw();
	goldCube->SetPosition(0.5 + 30, 1.5, -58);
	goldCube->Draw();
	// Layer 3
	goldCube->SetPosition(-1 + 30, 2, -58);
	goldCube->Draw();
	goldCube->SetPosition(-0 + 30, 2, -58);
	goldCube->Draw();
	goldCube->SetPosition(1 + 30, 2, -58);
	goldCube->Draw();
	// Layer 4
	goldCube->SetPosition(-0.5 + 30, 2.5, -58);
	goldCube->Draw();
	goldCube->SetPosition(0.5 + 30, 2.5, -58);
	goldCube->Draw();
	// Layer 5
	goldCube->SetPosition(0 + 30, 3, -58);
	goldCube->Draw();
	// End of cube coin

	// X Cube Coin
	// Layer 1
	goldCube->SetPosition(0 + 36, 1, 0 + -58);
	goldCube->Draw();
	// Layer 2
	goldCube->SetPosition(-0.5 + 36, 1.5, -58);
	goldCube->Draw();
	goldCube->SetPosition(0.5 + 36, 1.5, -58);
	goldCube->Draw();
	// Layer 3
	goldCube->SetPosition(-1 + 36, 2, -58);
	goldCube->Draw();
	goldCube->SetPosition(-0 + 36, 2, -58);
	goldCube->Draw();
	goldCube->SetPosition(1 + 36, 2, -58);
	goldCube->Draw();
	// Layer 4
	goldCube->SetPosition(-0.5 + 36, 2.5, -58);
	goldCube->Draw();
	goldCube->SetPosition(0.5 + 36, 2.5, -58);
	goldCube->Draw();
	// Layer 5
	goldCube->SetPosition(0 + 36, 3, -58);
	goldCube->Draw();
	// End of cube coin


	// Flag red side
	for (int j = 0; j < 3; j++) {
		redCube->SetPosition(31 + 3 + j, 11 - 1, -2 + -65);
		redCube->Draw();
	}

	// Flag white side
	for (int j = 0; j < 3; j++) {
		whiteCube->SetPosition(31 + 3 + j, 10 - 1, -2 + -65);
		whiteCube->Draw();
	}
	// Pole
	for (int i = 0; i < 7; i++) {
		cube->SetPosition(2 + 31, i + 5 - 1, -2 + -65);
		cube->SetRotation(0, 0, 1, 0);
		cube->Draw();
	}
	// 1st floor
	for (int j = 0; j < 5; j++) {
		for (int k = 0; k < 5; k++) {
			cube->SetPosition(k + 31, 0 -1, -j + -65);
			cube->SetRotation(0, 0, 1, 0);
			cube->Draw();
		}
	}
	// 2nd floor
	for (int j = 0; j < 4; j++) {
		for (int k = 0; k < 4; k++) {
			cube->SetPosition(0.5 + k + 31, 1 - 1, -0.5 - j + -65);
			cube->SetRotation(0, 0, 1, 0);
			cube->Draw();
		}
	}
	// 3rd floor
	for (int j = 0; j < 3; j++) {
		for (int k = 0; k < 3; k++) {
			cube->SetPosition(1 + k + 31, 2 - 1, -1 - j + -65);
			cube->SetRotation(0, 0, 1, 0);
			cube->Draw();
		}
	}
	// 4th floor
	for (int j = 0; j < 2; j++) {
		for (int k = 0; k < 2; k++) {
			cube->SetPosition(1.5 + k + 31, 3 - 1, -1.5 - j + -65);
			cube->SetRotation(0, 0, 1, 0);
			cube->Draw();
		}
	}
	// 5th floor
	for (int j = 0; j < 1; j++) {
		for (int k = 0; k < 1; k++) {
			cube->SetPosition(2 + k + 31, 4 - 1, -2 - j + -65);
			cube->SetRotation(0, 0, 1, 0);
			cube->Draw();
		}
	}

	// Torch
	torchCube->SetScale(0.1f, 0.3f, 0.1f);
	torchCube->SetPosition(15*2, 3.0, 1 + 0.25);
	torchCube->Draw();
	torchCube->SetPosition(15*2, 4.0, 1 + 0.25);
	torchCube->Draw();
	fireCube->SetPosition(15*2, 14.0, 1 + 0.25);
	fireCube->SetScale(0.1f, 0.1f, 0.1f);
	fireCube->Draw();

	torchCube->SetScale(0.1f, 0.3f, 0.1f);
	torchCube->SetPosition(25 * 2, 3.0, 1 + 0.25);
	torchCube->Draw();
	torchCube->SetPosition(25 * 2, 4.0, 1 + 0.25);
	torchCube->Draw();
	fireCube->SetPosition(25 * 2, 14.0, 1 + 0.25);
	fireCube->SetScale(0.1f, 0.1f, 0.1f);
	fireCube->Draw();

	torchCube->SetScale(0.1f, 0.3f, 0.1f);
	torchCube->SetPosition(35 * 2, 3.0, 1 + 0.25);
	torchCube->Draw();
	torchCube->SetPosition(35 * 2, 4.0, 1 + 0.25);
	torchCube->Draw();
	fireCube->SetPosition(35 * 2, 14.0, 1 + 0.25);
	fireCube->SetScale(0.1f, 0.1f, 0.1f);
	fireCube->Draw();

	torchCube->SetScale(0.1f, 0.3f, 0.1f);
	torchCube->SetPosition(45 * 2, 3.0, 1 + 0.25);
	torchCube->Draw();
	torchCube->SetPosition(45 * 2, 4.0, 1 + 0.25);
	torchCube->Draw();
	fireCube->SetPosition(45 * 2, 14.0, 1 + 0.25);
	fireCube->SetScale(0.1f, 0.1f, 0.1f);
	fireCube->Draw();
	// End of torch

	// Photo Frame
	//// Top
	//photoFrame->SetPosition(8 + 13, 3 + 3, 1.5 + 2); photoFrame->Draw();
	//photoFrame->SetPosition(9 + 13, 3 + 3, 1.5 + 2); photoFrame->Draw();
	//photoFrame->SetPosition(10 + 13, 3 + 3, 1.5 + 2); photoFrame->Draw();
	//photoFrame->SetPosition(11 + 13, 3 + 3, 1.5 + 2); photoFrame->Draw();
	//photoFrame->SetPosition(12 + 13, 3 + 3, 1.5 + 2); photoFrame->Draw();
	//// Right
	//photoFrame->SetPosition(12 + 13, 4 + 3, 1.5 + 2); photoFrame->Draw();
	//photoFrame->SetPosition(12 + 13, 5 + 3, 1.5 + 2); photoFrame->Draw();
	//photoFrame->SetPosition(12 + 13, 6 + 3, 1.5 + 2); photoFrame->Draw();
	//photoFrame->SetPosition(12 + 13, 7 + 3, 1.5 + 2); photoFrame->Draw();
	//// Left
	//photoFrame->SetPosition(8 + 13, 4 + 3, 1.5 + 2); photoFrame->Draw();
	//photoFrame->SetPosition(8 + 13, 5 + 3, 1.5 + 2); photoFrame->Draw();
	//photoFrame->SetPosition(8 + 13, 6 + 3, 1.5 + 2); photoFrame->Draw();
	//photoFrame->SetPosition(8 + 13, 7 + 3, 1.5 + 2); photoFrame->Draw();
	//// Bottom
	//photoFrame->SetPosition(8 + 13, 8 + 3, 1.5 + 2); photoFrame->Draw();
	//photoFrame->SetPosition(9 + 13, 8 + 3, 1.5 + 2); photoFrame->Draw();
	//photoFrame->SetPosition(10 + 13, 8 + 3, 1.5 + 2); photoFrame->Draw();
	//photoFrame->SetPosition(11 + 13, 8 + 3, 1.5 + 2); photoFrame->Draw();
	//photoFrame->SetPosition(12 + 13, 8 + 3, 1.5 + 2); photoFrame->Draw();

	// Rock
	// Rock 1
	rock->SetPosition(10, -1, 2); rock->Draw();
	rock->SetPosition(11, -1, 2); rock->Draw();
	rock->SetPosition(10, -1, 1); rock->Draw();
	rock->SetPosition(11, -1, 1); rock->Draw();
	rock->SetPosition(12, -1, 1); rock->Draw();
	rock->SetPosition(10, 0, 1); rock->Draw();
	rock->SetPosition(10, 0, 2); rock->Draw();
	rock->SetPosition(11, 0, 1); rock->Draw();
	// Rock 2
	rock->SetPosition(0, -1, 2); rock->Draw();
	rock->SetPosition(-1, -1, 2); rock->Draw();
	rock->SetPosition(0, -1, 1); rock->Draw();
	rock->SetPosition(-1, -1, 1); rock->Draw();
	rock->SetPosition(-2, -1, 1); rock->Draw();
	rock->SetPosition(0, 0, 1); rock->Draw();
	rock->SetPosition(0, 0, 2); rock->Draw();
	rock->SetPosition(-1, 0, 1); rock->Draw();
	// End of rock

	glDisable(GL_DEPTH_TEST);
}


void Application::ProcessInput(GLFWwindow* window)
{
	// Camera
	camera->ProcessInput(window, screenHeight, screenWidth, blockPositions);

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


int main(int argc, char** argv) {
	Application app = Application();
	app.Start("Simple Maze", 800, 600, false, false);
}