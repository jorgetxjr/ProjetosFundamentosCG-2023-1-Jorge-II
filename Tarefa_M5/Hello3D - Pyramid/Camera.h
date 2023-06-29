#pragma once
#define CAMERA_H

#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

// GLAD
#include <glad/glad.h>

// GLFW
#include <GLFW/glfw3.h>

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
	unsigned int shaderID;
	//construtor(?)
	Camera(unsigned int shaderid)
	{
		shaderID = shaderid;
	}

	//model matrix
	void prepararModel()
	{
		glm::mat4 model = glm::mat4(1); //matriz identidade;
		GLint modelLoc = glGetUniformLocation(shaderID, "model");
		//esta penúltima linha é necessária?
		model = glm::rotate(model, /*(GLfloat)glfwGetTime()*/glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, FALSE, glm::value_ptr(model));
	}
	//view matrix
	void prepararView()
	{
		glm::mat4 view = glm::lookAt(glm::vec3(0.0, 0.0, 3.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
		GLint viewLoc = glGetUniformLocation(shaderID, "view");
		glUniformMatrix4fv(viewLoc, 1, FALSE, glm::value_ptr(view));
	}

	//projection matrix
	void prepararProjection(float width, float height)
	{
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
		GLint projLoc = glGetUniformLocation(shaderID, "projection");
		glUniformMatrix4fv(projLoc, 1, FALSE, glm::value_ptr(projection));
	}

	void iniciarCamera(float width, float height)
	{
		this->prepararModel();
		this->prepararView();
		this->prepararProjection(width, height);

		//return true;
	}
	void moverCamera(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp)
	{
		cameraFront += cameraPos;
		glm::mat4 view = glm::lookAt(cameraPos, cameraFront, cameraUp);
		GLint viewLoc = glGetUniformLocation(shaderID, "view");
		glUniformMatrix4fv(viewLoc, 1, FALSE, glm::value_ptr(view));
	}





	//passar dados para o shader OK
	//armazenar a posição e orientação da câmera OK
	//mexo em callback? eu nem sei direito o que essa callback!


};
