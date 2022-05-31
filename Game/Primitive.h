#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "Mesh.h"

class Primitive : public Mesh
{
public: 
	Primitive();
	unsigned int loadCubemap(std::vector<std::string> faces);

	void setup() override;
	void draw() override;
	
private:
	
	std::vector<GLint> indices;
	std::vector<GLfloat> vertices;
	std::vector<GLfloat> normals;
	std::vector<GLfloat> colors;

	unsigned int cubemapTexture;

	GLuint VBO_color;
	GLuint VBO_normal;
	GLuint VBO_vertex;
	GLuint VBO_shadowVertex;
	GLuint VBO_texture;
	GLuint VBO_tangent;
	GLuint VBO_bitangent;

	GLuint ID_texture;
	GLint ID_vertex;
	GLint ID_color;
	GLint ID_normal;
	GLint ID_tangent;
	GLint ID_bitangent;

};

#endif;
