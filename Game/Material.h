#ifndef MATERIAL_H
#define MATERIAL_H

#include "Texture.h"
#include "Shader.h"

class Material
{
public:
	Material();
	~Material() {};

	void setShader(Shader* shader);
	void loadShader(std::string shaderID);
	void loadMaterialFile(std::string name);
	void sendData();
	void reset(); //Resets to default

private:

	Shader* shader;

	Texture* t_ambient;
	Texture* t_specular;
	Texture* t_diffuse;
	Texture* t_normal;

	glm::vec3 ambient = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 diffuse = glm::vec3(1.0f);
	glm::vec3 specular = glm::vec3(1.0f);
	
	float shininess;
	float reflectivity;
	float transparency;
	float refractionIndex;

	static std::map<std::string, Material>* s_materialMap;
	static std::map<std::string, Shader>* s_shaderMap;
};
#endif
