#ifndef MATERIAL_H
#define MATERIAL_H

#include "Texture.h"
#include "Shader.h"

class Material
{
public:
	Material();
	~Material() {};

private:

	Shader shader;
};
#endif
