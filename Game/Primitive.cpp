#include "Primitive.h"

Primitive::Primitive()
{
	buffer = new Buffer();
}

Primitive::~Primitive()
{
}

void Primitive::setup()
{
	mat = new Material();
	mat->loadShader("default"); //TODO: Make this work
	//Setup indices
	indices = { 
		0,1,
		3,3,
		1,2,
		4,5,
		7,7,
		5,6,
		8,9,
		11,11,
		9,10,
		12,13,
		15,15,
		13,14,
		16,17,
		19,19,
		17,18,
		20,21,
		23,23,
		21,22 };

	vertices = {
		-0.5f,0.5f,
		0.5f,0.5f,
		0.5f,0.5f,
		0.5f,-0.5f,
		0.5f,-0.5f,
		-0.5f,0.5f,
		-0.5f,0.5f,
		-0.5f,0.5f,
		0.5f,-0.5f,
		0.5f,-0.5f,
		-0.5f,-0.5f,
		-0.5f,-0.5f,
		-0.5f,0.5f,
		-0.5f,-0.5f,
		0.5f,0.5f,
		-0.5f,-0.5f,
		0.5f,-0.5f,
		-0.5f,-0.5f,
		0.5f,0.5f,
		-0.5f,0.5f,
		0.5f,0.5f,
		0.5f,-0.5f,
		0.5f,0.5f,
		-0.5f,-0.5f,
		-0.5f,-0.5f,
		-0.5f,0.5f,
		-0.5f,-0.5f,
		0.5f,-0.5f,
		0.5f,-0.5f,
		-0.5f,0.5f,
		-0.5f,0.5f,
		-0.5f,0.5f,
		0.5f,-0.5f,
		0.5f,0.5f,
		0.5f,-0.5f,
		0.5f,0.5f
	};

	normals = {
		0.0f,0.0f,
		1.0f,0.0f,
		0.0f,1.0f,
		0.0f,0.0f,
		1.0f,0.0f,
		0.0f,1.0f,
		0.0f,0.0f,
		-1.0f,0.0f,
		0.0f,-1.0f,
		0.0f,0.0f,
		-1.0f,0.0f,
		0.0f,-1.0f,
		-1.0f,0.0f,
		0.0f,-1.0f,
		0.0f,0.0f,
		-1.0f,0.0f,
		0.0f,-1.0f,
		0.0f,0.0f,
		1.0f,0.0f,
		0.0f,1.0f,
		0.0f,0.0f,
		1.0f,0.0f,
		0.0f,1.0f,
		0.0f,0.0f,
		0.0f,-1.0f,
		0.0f,0.0f,
		-1.0f,0.0f,
		0.0f,-1.0f,
		0.0f,0.0f,
		-1.0f,0.0f,
		0.0f,1.0f,
		0.0f,0.0f,
		1.0f,0.0f,
		0.0f,1.0f,
		0.0f,0.0f,
		1.0f,0.0f 
	};

	//Set color was white
	glm::vec3 temp_rgb = mat->getAmbient();
	
	//Temp Color array for cube colors
	GLfloat tempColors[]{ temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,								//#face1 front
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,

						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,								//#face2 back
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,

						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,								//#face2 left
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,

						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,								//#face2 right
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,

						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,								//#face2 top
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,

						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,								//#face2 bottom
						  temp_rgb.x, temp_rgb.y, temp_rgb.z,
						  temp_rgb.x, temp_rgb.y, temp_rgb.z
	};

	for (size_t i = 0; i < 72; i++)
	{
		colors.push_back(tempColors[i]);
	}

	//Set EBO/VAO and VBOs to default
	EBO = 0;
	VAO = 0;
	VBO_color = 0;
	VBO_vertex = 0;
	VBO_normal = 0;

	buffer->GenerateVertexArrays(1, &VAO);
	buffer->BindVertexArrays(VAO);

	buffer->GenerateBuffers(1, &VBO_vertex);
	buffer->BindBuffer(GL_ARRAY_BUFFER, VBO_vertex);
	buffer->FillBuffer(GL_ARRAY_BUFFER, vertices, GL_STATIC_DRAW);
	buffer->LinkToShader(ID_vertex, 3, GL_FLOAT, GL_FALSE, 0, 0);
	buffer->EnableVertexArray(ID_vertex);

	buffer->GenerateBuffers(1, &VBO_color);
	buffer->BindBuffer(GL_ARRAY_BUFFER, VBO_color);
	buffer->FillBuffer(GL_ARRAY_BUFFER, colors, GL_STATIC_DRAW);
	buffer->LinkToShader(ID_color, 3, GL_FLOAT, GL_FALSE, 0, 0);
	buffer->EnableVertexArray(ID_color);

	buffer->GenerateBuffers(1, &EBO);
	buffer->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	buffer->FillBuffer(GL_ELEMENT_ARRAY_BUFFER, indices, GL_STATIC_DRAW);
	buffer->BindVertexArrays(0);
}

void Primitive::draw()
{
	mat->getShader().Use();
	mat->getShader().setMat4("model", model);
	mat->getShader().setVec3("ambient", ambient);
	mat->getShader().setVec3("specular", specular);
	mat->getShader().setVec3("diffuse", diffuse);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	//mat->getShader().SetMatrix4("model", glm::value_ptr(model), GL_FALSE);

}
