#include "Material.h"

std::map<std::string, Shader>* Shader::s_shaderMap = new std::map<std::string, Shader>;

Material::Material()
{
	
}

void Material::setShader(Shader* shader)
{
	this->shader = shader;
}

void Material::loadShader(std::string shaderID)
{
	bool isInMap = false;
	std::map<std::string, Shader>::iterator it;

	it = s_shaderMap->find(shaderID);

	if (it != s_shaderMap->end())
	{
		isInMap = true;
		this->shader = &it->second; //TODO: Check if this works
	}

	//Check if texture is in map
	if (isInMap == false)
	{
		std::string tempString = "Texture: " + shaderID + " can not be found!";
		//TheDebug::Log(tempString, ALERT); //TODO: Add debug log
	}
}

void Material::loadMaterialFile(std::string name)
{
	loadShader("Default");
}

void Material::sendData()
{
	if (t_ambient == nullptr)
		shader->setUniform("ambient", ambient);
	//TODO: Add else

	if (t_diffuse == nullptr)
		shader->setUniform("diffuse", diffuse);

	if(t_specular)
		shader->setUniform("specular", specular);

}

Shader Material::getShader()
{
	return *shader;
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
