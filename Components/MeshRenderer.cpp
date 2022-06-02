#include "MeshRenderer.h"
#include "../Game/GameObject.h"
#include "../Application/Renderer.h"

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
	//gameObject->getTransform()->sendData(*mat->getShader());
	gameObject->getTransform()->sendData(Renderer::instance()->getShader(shader));
	//gameObject->getTransform()->sendData(Renderer::instance()->getShader("Default"));
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

void MeshRenderer::setShader(std::string shader)
{
	this->shader = shader;
}

std::shared_ptr<Material> MeshRenderer::getMaterial()
{
	return mat;
}
