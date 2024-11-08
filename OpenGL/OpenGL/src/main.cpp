#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "Buffers_data.h"
#include "Shader.h"
#include "Texture.h"


void movement(GLFWwindow* window, float& x, float& y)
{
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		x += 0.01f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		x -= 0.01f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		y += 0.01f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		y -= 0.01f;
}


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(600, 600, "window", nullptr, nullptr);
	if (!window)
	{
		std::cerr << "Can not craete window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Can not use glad" << std::endl;
		glfwTerminate();
		return -2;
	}

	//Shaders
	Shader shader("shaders//vertex_shader.txt", "shaders//fragment_shader.txt");

	//Textures
	Texture texture_container;
	texture_container.use_texture_unit(0);
	texture_container.bind();
	texture_container.set_params();
	texture_container.load_texture_jpg("images//container.jpg");

	Texture texture_awesomeface;
	texture_awesomeface.use_texture_unit(1);
	texture_awesomeface.bind();
	texture_awesomeface.set_params();
	texture_awesomeface.load_texture_png("images//awesomeface.png");

	//buffers
	GLuint EBO, VBO, VAO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);


	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);


	shader.use();
	shader.setInt("container", 0);
	shader.setInt("awesomeface", 1);

	//math prepare
	float x = 0.0f;
	float y = 0.0f;


	//settings for window
	glClearColor(0.3f, 0.5f, 0.5f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);


		shader.use();

		//math part
		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.0f));
		movement(window, x, y);
		trans = glm::translate(trans, glm::vec3(x, y, 0.0f));
		shader.setMat4("transform", trans);

		texture_container.use_texture_unit(0);
		texture_container.bind();
		texture_awesomeface.use_texture_unit(1);
		texture_awesomeface.bind();

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}