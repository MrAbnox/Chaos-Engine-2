#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material mat)
{
	this->vertices = vertices;
	this->indices = indices;
	this->mat = &mat;
}

void Mesh::draw()
{
	
}

void Mesh::setupMesh()
{

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