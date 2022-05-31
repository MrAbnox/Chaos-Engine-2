#ifndef MODEL_H
#define MODEL_H

#include "glad/glad.h"
#include "Texture.h"
#include "Buffer.h"
#include "Mesh.h"

#include <string>

//struct to store all three components of a vertex group, which is
//the grouping of verts, UVs and norms for each point in a triangle
struct Groups
{
	glm::vec3 vertex;
	glm::vec2 texture;
	glm::vec3 normal;
};

class Model : public Mesh
{

public:

	Model();

public:


public:

	bool loadObj(const std::string& filepath);
	bool loadModel(const std::string& filename);
	bool loadTexture(const std::string& filename, const std::string textureID);
	//void UnloadTexture(const std::string textureID); Maybe delete?
	//void LoadNormalMap(std::string filepath);		   Maybe delete?
	//void LoadHeightMap(std::string filepath);		   Maybe delete?

public:

	void Create(std::string shader);
	void Update();
	void Draw();
	void Destroy();


public:

	GLint& getIsTextured();
	void SetShininess(GLfloat shininess);

	//void SetAmbient(GLfloat r, GLfloat g, GLfloat b);	   Maybe delete this and access through material
	//void SetDiffuse(GLfloat r, GLfloat g, GLfloat b);	   Maybe delete this and access through material
	//void SetSpecular(GLfloat r, GLfloat g, GLfloat b);   Maybe delete this and access through material

	void SetPosition(GLfloat x, GLfloat y, GLfloat z);
	void SetRotation(GLfloat x, GLfloat y, GLfloat z);
	void SetScale(GLfloat x, GLfloat y, GLfloat z);
private:
	bool is_near(float v1, float v2);
	bool getSimilarVertexIndex(glm::vec3& in_vertex, glm::vec2& in_uv, glm::vec3& in_normal, std::vector<glm::vec3>& out_vertices,
		std::vector<glm::vec2>& out_uvs, std::vector<glm::vec3>& out_normals, unsigned short& result);
	void indexVBO_slow(
		std::vector<glm::vec3>& in_vertices,
		std::vector<glm::vec2>& in_uvs,
		std::vector<glm::vec3>& in_normals,

		std::vector<unsigned short>& out_indices,
		std::vector<glm::vec3>& out_vertices,
		std::vector<glm::vec2>& out_uvs,
		std::vector<glm::vec3>& out_normals
	);
	void indexVBO(
		std::vector<glm::vec3>& in_vertices,
		std::vector<glm::vec2>& in_uvs,
		std::vector<glm::vec3>& in_normals,

		std::vector<GLuint>& out_indices,
		std::vector<glm::vec3>& out_vertices,
		std::vector<glm::vec2>& out_uvs,
		std::vector<glm::vec3>& out_normals
	);

	void CalculateTangents(// inputs
		std::vector<glm::vec3>& vertices,
		std::vector<glm::vec2>& uvs,
		std::vector<glm::vec3>& normals,
		// outputs
		std::vector<glm::vec3>& tangents,
		std::vector<glm::vec3>& bitangents);

private:

	GLfloat shininess;
	GLint isTextured;

	Buffer* buffer;

private:

	GLuint VAO;
	GLuint EBO;
	GLuint vertexVBO;
	GLuint colorVBO;
	GLuint normalVBO;
	GLuint textureVBO;
	GLuint totalVertices;
	GLuint VBO_tangent;
	GLuint VBO_bitangent;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<GLuint> indices;

	std::vector<GLfloat> tangents;
	std::vector<GLfloat> bitangents;

private:

	GLuint ID_vertex;
	GLuint ID_normal;
	GLuint ID_texture;
	GLuint ID_tangent;
	GLuint ID_bitangent;
	GLuint ID_color;

private:

	glm::mat3 normal;

private:

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

private:

	Texture texture;
	Texture normalMap;
	Texture heightMap;

private:

	std::string shader;

	bool firstML;

	int isHeightMapped;

	int isShadowMapped;
	int isNormalMapped;
};

#endif