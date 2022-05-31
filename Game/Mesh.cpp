#include "Mesh.h"

std::map<std::string, GLint>* Mesh::s_IDMap = new std::map <std::string, GLint>;

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material mat)
{
	this->vertices = vertices;
	this->indices = indices;
	this->mat = &mat;
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

void Mesh::setupVertices(std::vector<Vertex> vertices)
{
	this->vertices = vertices;
}
void Mesh::setupIndices(std::vector<unsigned int> indices)
{
	this->indices = indices;
}
void Mesh::setupMaterial(Material mat)
{
	this->mat = &mat;
}

Material* Mesh::getMaterial()
{
	return mat;
}
