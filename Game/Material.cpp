#include "Material.h"


Material::Material()
{
	
}

void Material::setShader(Shader* shader)
{
	this->shader = shader;
}

void Material::loadMaterialFile(std::string name)
{
}

void Material::sendData()
{
	//if (t_ambient == nullptr)
	//	shader->setUniform("ambient", ambient);
	////TODO: Add else

	//if (t_diffuse == nullptr)
	//	shader->setUniform("diffuse", diffuse);

	//if(t_specular)
	//	shader->setUniform("specular", specular);
}

void Material::reset()
{
}

Shader* Material::getShader()
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
