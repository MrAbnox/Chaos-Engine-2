#include "Texture.h"
#include <string>
#include <stb_image.h>
#include "../Utility/Debug.h"
#include "../Application/Renderer.h"

Texture::Texture()
{
	
}


void Texture::init(int width, int height, unsigned char** data, GLenum textureTarget, GLfloat* filter, GLenum* internalFormat, GLenum* format, bool clamp, GLenum* attachment)
{
	height = height;
	width = width;
	glGenTextures(1, &ID);

	glBindTexture(textureTarget, ID);

	glTexParameterf(textureTarget, GL_TEXTURE_MIN_FILTER, filter[0]);
	glTexParameterf(textureTarget, GL_TEXTURE_MAG_FILTER, filter[0]);

	if (clamp)
	{
		//TODO: Fix clamp
		//glTexParameterf(textureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP);
		//glTexParameterf(textureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);

	glTexImage2D(textureTarget, 0, internalFormat[0], width, height, 0, format[1], GL_UNSIGNED_BYTE, data);


	GLenum drawBuffers[32];      //32 is the max number of bound textures in OpenGL //Assert to be sure no buffer overrun should occur

	bool hasDepth = false;

	if (attachment[0] == GL_DEPTH_ATTACHMENT)
	{
		drawBuffers[0] = GL_NONE;
		hasDepth = true;
	}
	else
	{
		drawBuffers[0] = attachment[0];
	}


	if (attachment[0] == GL_NONE)
	{
		if (frameBuffer == 0)
		{
			glGenFramebuffers(1, &frameBuffer);
			glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
		}

		glFramebufferTexture2D(GL_FRAMEBUFFER, attachment[0], textureTarget, ID, 0);
		if (!frameBuffer == 0)
		{
			if (!hasDepth)
			{
				glGenRenderbuffers(1, &renderBuffer);
				glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
				glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);
			}

			glDrawBuffers(1, drawBuffers);

			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			{
				Debug::Log("Framebuffer creation failed!", ALERT);
			}

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}
}


//TODO: Check if texture was already loaded
GLuint Texture::loadTexture(const std::string& fName)
{
	std::string filename = fName;

	unsigned int textureID;
	glGenTextures(1, &textureID);
	std::cout << "Gen ID: " << textureID << std::endl;
	//Renderer::instance()->getShader("Default").Use();

	int width, height, nrComponents;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(data);
	}
	else
	{
		Debug::Log("Texture failed to load at path:" + fName); 
		stbi_image_free(data);
		return false;
	}

	ID = textureID;
	return textureID;
}

void const Texture::bind() const
{
	//Bind texture
	glBindTexture(GL_TEXTURE_2D, ID);

	if (ID < 0)
	{
		Debug::Log("Texture ID could not be bound", ALERT);
	}
}

void const Texture::unbind() const
{
	//Bind texture
	glBindTexture(GL_TEXTURE_2D, 0);

	if (ID < 0)
	{
		Debug::Log("Texture ID could not be bound", ALERT);
	}
}

unsigned int Texture::getID() const
{
	return ID;
}

void Texture::setID(GLuint id)
{
	ID = id;
}
