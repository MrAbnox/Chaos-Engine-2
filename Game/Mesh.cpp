#include "Mesh.h"

Mesh::Mesh()
{

}

void Mesh::setup()
{

}

void Mesh::draw()
{
	
}

unsigned int Mesh::getVAO()
{
	return VAO;
}

void Mesh::setupMaterial(std::shared_ptr<Material> mat)
{
	this->mat = mat;
}

std::shared_ptr<Material> Mesh::getMaterial()
{
	return mat;
}