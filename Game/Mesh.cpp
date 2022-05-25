#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material mat)
{
	this->vertices = vertices;
	this->indices = indices;
	this->mat = mat;
}

void Mesh::draw()
{
	
}

void Mesh::setupMesh()
{

}