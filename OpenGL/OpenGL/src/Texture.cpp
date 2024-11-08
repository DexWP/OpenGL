#include "Texture.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

Texture::Texture() noexcept
{
	glGenTextures(1, &texture);
}

void Texture::use_texture_unit(int texture_unit) const
{
	switch (texture_unit)
	{
	case 0:		glActiveTexture(GL_TEXTURE0);		break;
	case 1:		glActiveTexture(GL_TEXTURE1);		break;
	case 2:		glActiveTexture(GL_TEXTURE2);		break;
	case 3:		glActiveTexture(GL_TEXTURE3);		break;
	case 4:		glActiveTexture(GL_TEXTURE4);		break;
	case 5:		glActiveTexture(GL_TEXTURE5);		break;
	case 6:		glActiveTexture(GL_TEXTURE6);		break;
	case 7:		glActiveTexture(GL_TEXTURE7);		break;
	case 8:		glActiveTexture(GL_TEXTURE8);		break;
	case 9:		glActiveTexture(GL_TEXTURE9);		break;
	}
}

void Texture::load_texture_jpg(const char* texturePath) const
{
	stbi_set_flip_vertically_on_load(true);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
	if (!data)
	{
		std::cerr << "Can not load texture" << std::endl;
		glfwTerminate();
		return;
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	stbi_image_free(data);
}

void Texture::load_texture_png(const char* texturePath) const
{
	stbi_set_flip_vertically_on_load(true);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
	if (!data)
	{
		std::cerr << "Can not load texture" << std::endl;
		glfwTerminate();
		return;
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	stbi_image_free(data);
}

void Texture::set_params() const
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, texture);
}