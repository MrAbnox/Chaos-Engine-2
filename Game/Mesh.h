#ifndef MESH_H
#define MESH_H

#include <glm/matrix.hpp>
#include <vector>
#include "Material.h"
#include "Buffer.h"

class Mesh
{
public:
    Mesh();

    void setupMaterial(std::shared_ptr<Material> mat); //Maybe delete this

    std::shared_ptr<Material> getMaterial();

public:
    virtual void setup();
    virtual void draw(); //TODO: Maybe pass shader in here?

    unsigned int getVAO();
	
protected:
    std::shared_ptr<Material> mat; //TODO: Maybe make this a pointer?
    Buffer* buffer;
	
protected:
	
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

    GLuint ID_vertex;
    GLuint ID_normal;
    GLuint ID_texture;
    GLuint ID_tangent;
    GLuint ID_bitangent;
    GLuint ID_color;

private:

    Texture texture;
    Texture normalMap;
    Texture heightMap;
};

#endif