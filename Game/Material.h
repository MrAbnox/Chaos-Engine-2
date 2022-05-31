#ifndef MATERIAL_H
#define MATERIAL_H

#include "Texture.h"
#include "Shader.h"
#include <vector>
#include <memory>

enum Type {
	DEFAULT, SKYBOX
};

class Material
{
public:
	Material(Type type = DEFAULT);
	Material(const Material&); // copy constructor	

	void setShader(std::shared_ptr<Shader> shader);
	void loadMaterialFile(std::string name);
	void sendData();
	void reset(); //Resets to default

	//unsigned int loadCubemap(std::vector<std::string> faces);

	std::shared_ptr<Shader> getShader();
	glm::vec3 getAmbient();
	glm::vec3 getDiffuse();
	glm::vec3 getSpecular();
	float getShininess();
	float getReflectivity();
	float getTransparency();

private:

	std::shared_ptr<Shader> shader;

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
	Type type;

	unsigned int cubemapTexture;
	//float refractionIndex;
};
#endif
