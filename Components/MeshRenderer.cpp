#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(GameObject* gameObject) : Component(gameObject)
{
	this->gameObject = gameObject;
	castShadows = false;
}

MeshRenderer::~MeshRenderer()
{
}

//Maybe remove this function
void MeshRenderer::update()
{
}

void MeshRenderer::render()
{
	mesh->draw();
}

//Maybe remove this function
void MeshRenderer::fixedUpdate(float deltaTime)
{
}

void MeshRenderer::setMesh(Mesh& mesh)
{
	this->mesh = &mesh;
}

void MeshRenderer::setMaterial(Material& mat)
{
	this->mat = &mat;
}

void MeshRenderer::setCastShadows(bool castShadows)
{
	this->castShadows = castShadows;
}

Material& MeshRenderer::getMaterial()
{
	return *mat;
}
