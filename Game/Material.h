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

	void start();

	void setShader(std::shared_ptr<Shader> shader);
	void loadMaterialFile(std::string name);
	void sendData();
	void reset(); //Resets to default

	//unsigned int loadCubemap(std::vector<std::string> faces);
	void loadTexture(const std::string& filename);
	void setAmbientTexture(std::shared_ptr<Texture> t);

	std::shared_ptr<Shader> getShader();
	glm::vec3 getAmbient();
	glm::vec3 getDiffuse();
	glm::vec3 getSpecular();
	
	std::shared_ptr<Texture> getAmbientTexture();
	std::shared_ptr<Texture> getSpecularTexture();
	std::shared_ptr<Texture> getDiffuseTexture();
	std::shared_ptr<Texture> getNormalMap();
	std::shared_ptr<Texture> getHeightMap();

	float getShininess();
	float getReflectivity();
	float getTransparency();

private:

	std::shared_ptr<Shader> shader;

	std::shared_ptr<Texture> ambientTexture;
	std::shared_ptr<Texture> specularTexture;
	std::shared_ptr<Texture> diffuseTexture;
	std::shared_ptr<Texture> normalMap;
	std::shared_ptr<Texture> heightMap;

	glm::vec3 ambient = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 diffuse = glm::vec3(1.0f);
	glm::vec3 specular = glm::vec3(1.0f);
	Type type;
	
	float shininess;
	float reflectivity;
	float transparency;

	unsigned int cubemapTexture;
};
#endif
