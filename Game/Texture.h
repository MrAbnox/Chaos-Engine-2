#ifndef TEXTURE_H
#define TEXTURE_H

#include "glad/glad.h"
#include <map>
#include <string>

enum Filters
{
	NEAREST = GL_NEAREST,
	BILINEAR = GL_LINEAR,
	TRILINEAR = GL_LINEAR_MIPMAP_LINEAR,
	MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
	MIPMAP_NEAREST_BILINEAR = GL_NEAREST_MIPMAP_LINEAR,
	MIPMAP_BILINEAR_NEAREST = GL_LINEAR_MIPMAP_NEAREST
};

enum Wrappers
{
	REPEAT = GL_REPEAT,
	MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
	CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE
};

enum FilterOptions
{
	MIN = GL_TEXTURE_MIN_FILTER,
	MAG = GL_TEXTURE_MAG_FILTER
};

enum WrapOptions
{
	WRAP_S = GL_TEXTURE_WRAP_S,
	WRAP_T = GL_TEXTURE_WRAP_T
};

class Texture
{
public:
	Texture();
	Texture(const Texture&); // copy constructor	

public:

	void init(int width, int height, unsigned char** data, GLenum textureTarget, GLfloat* filter, GLenum* internalFormat, GLenum* format, bool clamp, GLenum* attachment);
	GLuint loadTexture(const std::string& fName);
	void const bind() const;
	void const unbind() const;
	void setID(GLuint id);

private:

	int width;
	int height;

	unsigned int ID;
	Filters filter;
	GLuint frameBuffer;
	GLuint renderBuffer;
	GLboolean isBound;

	static std::map<std::string, Texture>* s_textureMap;
};

#endif
