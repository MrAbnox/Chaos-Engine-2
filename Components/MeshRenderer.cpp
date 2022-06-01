#include "MeshRenderer.h"
#include "../Game/GameObject.h"

MeshRenderer::MeshRenderer(GameObject* gameObject) : Component(gameObject)
{
	this->gameObject = gameObject;
	castShadows = false;
}

MeshRenderer::~MeshRenderer()
{
	std::cout;
}

//Maybe remove this function
void MeshRenderer::update()
{
	gameObject;
}

void MeshRenderer::render()
{
	mesh->draw();
	gameObject->getTransform()->sendData(*mat->getShader());
}

//Maybe remove this function
void MeshRenderer::fixedUpdate(float deltaTime)
{
}

void MeshRenderer::setMesh(std::shared_ptr<Mesh> mesh)
{
	this->mesh = mesh;
}

void MeshRenderer::setMaterial(std::shared_ptr<Material> mat)
{
	this->mat = mat;
}

void MeshRenderer::setCastShadows(bool castShadows)
{
	this->castShadows = castShadows;
}

std::shared_ptr<Material> MeshRenderer::getMaterial()
{
	return mat;
}
