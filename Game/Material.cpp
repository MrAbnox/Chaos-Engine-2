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
		
		//std::vector<std::string> faces
		//{
		//	"skybox/right.tga",
		//	"skybox/left.tga",
		//	"skybox/top.tga",
		//	"skybox/bottom.tga",
		//	"skybox/front.tga",
		//	"skybox/back.tga"
		//};
		//cubemapTexture = loadCubemap(faces);

		break;
	default:
		break;
	}

	
}

Material::Material(const Material &m)
{
	type = m.type;
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
	switch (type)
	{
	case DEFAULT:
		break;
	case SKYBOX:

		//glBindVertexArray(mesh.VAO);
		//glActiveTexture(GL_TEXTURE5);
		//glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		break;
	default:
		break;
	}
}

//unsigned int Material::loadCubemap(std::vector<std::string> faces)
//{
//	unsigned int textureID;
//	glGenTextures(1, &textureID);
//	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
//
//	int width, height, nrComponents;
//	for (unsigned int i = 0; i < faces.size(); i++)
//	{
//		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrComponents, 0);
//		if (data)
//		{
//			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_SRGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//			stbi_image_free(data);
//		}
//		else
//		{
//			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
//			stbi_image_free(data);
//		}
//	}
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_MIRRORED_REPEAT);
//
//	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
//
//	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
//
//	return textureID;
//}

void Material::reset()
{
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
