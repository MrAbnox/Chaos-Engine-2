#ifndef MESH_H
#define MESH_H

#include <glm/matrix.hpp>
#include <vector>
#include "Material.h"
#include "Buffer.h"

struct Vertex 
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
    glm::vec3 tangent;
    glm::vec3 bitangent;
};

class Mesh
{
public:
    Mesh() {};
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material mat);
	~Mesh();

    void setupVertices(std::vector<Vertex> vertices);
    void setupIndices(std::vector<unsigned int> indices);
    void setupMaterial(Material mat);

public:
    void draw(); //TODO: Maybe pass shader in here?
    void setupMesh();
	
protected:
    Material* mat; //TODO: Maybe make this a pointer?
    Buffer* buffer;
    unsigned int VAO, VBO, EBO;
private:

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    glm::mat4 model;
	
};

#endif