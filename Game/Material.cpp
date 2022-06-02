#include "Material.h"
#include <iostream>


Material::Material(Type type)
{
	this->type = type;

	switch (type)
	{
	case DEFAULT:
		break;
	case SKYBOX:
		break;
	default:
		break;
	}

	std::shared_ptr<Texture> t = std::make_shared<Texture>();
	setAmbientTexture(t);
}

Material::Material(const Material &m)
{
	type = m.type;
}

void Material::start()
{

}

void Material::setShader(std::shared_ptr<Shader> shader)
{
	this->shader = shader;
}

void Material::loadMaterialFile(std::string name)
{

}

void Material::sendData()
{

}

void Material::reset()
{
}

void Material::loadTexture(const std::string& filename)
{
	ambientTexture->loadTexture(filename);
}

void Material::setAmbientTexture(std::shared_ptr<Texture> t)
{
	ambientTexture = t;
}

std::shared_ptr<Shader> Material::getShader()
{
	return shader;
}

glm::vec3 Material::getAmbient()
{
	return ambient;
}

glm::vec3 Material::getDiffuse()
{
	return diffuse;
}

glm::vec3 Material::getSpecular()
{
	return specular;
}

std::shared_ptr<Texture> Material::getAmbientTexture()
{
	return ambientTexture;
}

std::shared_ptr<Texture> Material::getSpecularTexture()
{
	return specularTexture;
}

std::shared_ptr<Texture> Material::getDiffuseTexture()
{
	return diffuseTexture;
}

std::shared_ptr<Texture> Material::getNormalMap()
{
	return normalMap;
}

std::shared_ptr<Texture> Material::getHeightMap()
{
	return heightMap;
}

float Material::getShininess()
{
	return shininess;
}

float Material::getReflectivity()
{
	return reflectivity;
}

float Material::getTransparency()
{
	return transparency;
}
