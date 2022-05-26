#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "Mesh.h"

class Primitive : Mesh
{
public: 
	Primitive();
	~Primitive();

	void setup();

private:
	std::vector<GLint> indices;
	std::vector<GLfloat> vertices;
	std::vector<GLfloat> normals;
};

#endif;
