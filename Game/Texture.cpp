#include "Texture.h"
#include <string>

Texture::Texture()
{
	
}

void Texture::init(int width, int height, unsigned char** data, GLenum textureTarget, GLfloat* filter, GLenum* internalFormat, GLenum* format, bool clam, GLenum* attachment)
{
	height = height;
	width = width;
	glGenTextures(1, &ID);

	glBindTexture(textureTarget, ID);

	glTexParameterf(textureTarget, GL_TEXTURE_MIN_FILTER, filter[0]);
	glTexParameterf(textureTarget, GL_TEXTURE_MAG_FILTER, filter[0]);

	if (clam)
	{
		glTexParameterf(textureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameterf(textureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP);
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
				std::cerr << "Framebuffer creation failed!" << std::endl;
			}

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}
}

//bool Texture::Load(const std::string& filename, const std::string& IDRef)
//{
//	//-----------------------------
//	//Check if texture has already been loaded
//	//-----------------------------
//	bool isInMap = false;
//	std::map<std::string, Texture>::iterator it;
//
//	it = s_textureMap->find(IDRef);
//
//	if (it == s_textureMap->end())
//	{
//	}
//	else
//	{
//		isInMap = true;
//		*this = it->second;
//	}
//
//	//-----------------------------
//	//Load raw image into RAM
//	//-----------------------------
//
//	if (isInMap == false)
//	{
//		//Load the raw image data from file
//		SDL_Surface* textureData = IMG_Load(filename.c_str());
//
//		//----------------------------- If image data could not be loaded 
//
//		if (!textureData)
//		{
//			std::string tempS = "Error loading texture file " + filename;
//			TheDebug::Log(tempS, ALERT);
//
//			return false;
//		}
//
//		//Extract the raw mage data and store in variables for use below (easier)
//		GLsizei width = textureData->w;
//		GLsizei height = textureData->h;
//
//		Uint8* pixels = (Uint8*)textureData->pixels;
//		Uint8 depth = textureData->format->BytesPerPixel;
//		GLint format = (depth == 4) ? GL_RGBA : GL_RGB;
//
//
//		//----------------------------
//		//Create texture object in VRAM
//		//----------------------------
//
//		//Create the teture ID for our texture object(VRAM)
//		glGenTextures(1, &ID);
//
//		//Bind the texture ID
//		glBindTexture(GL_TEXTURE_2D, ID);
//
//		//Set default filtering options
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//
//		//Create the texture object in VRAM using the raw data extracted above
//		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);
//
//		//Create mipmap for textures
//		glGenerateMipmap(GL_TEXTURE_2D);
//
//		glBindTexture(GL_TEXTURE_2D, 0);
//
//		//Release RAM image
//		SDL_FreeSurface(textureData);
//
//		//Add the new texture image to the map
//		s_textureMap->insert(std::pair<std::string, Texture>(IDRef, *this));
//	}
//
//	return true;
//}
