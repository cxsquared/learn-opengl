#include "Texture.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stb_image.h>

Texture::Texture(std::string filePath)
{
	glGenTextures(1, &Id);
	glBindTexture(GL_TEXTURE_2D, Id);

	// set the texture wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(filePath.c_str(), &Width, &Height, &NrChannels, 0);
	// Load texture file
	if (data) 
	{
		if (NrChannels == 3)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else if (NrChannels == 4)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		else
		{
			std::cout << "Failed to load texture: " << filePath << std::endl;
		}

		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture: " << filePath << std::endl;
	}

	// unload image
	stbi_image_free(data);
}

Texture::~Texture()
{
	glDeleteTextures(1, &Id);
}