#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "Mesh.h"

class Primitive : Mesh
{
public: 
	Primitive();
	~Primitive();

	void setup();
	void draw();
	
private:
	
	std::vector<GLint> indices;
	std::vector<GLfloat> vertices;
	std::vector<GLfloat> normals;
	std::vector<GLfloat> colors;

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
