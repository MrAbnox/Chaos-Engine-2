#include <fstream>
#include <iostream>
#include <vector>
#include "Model.h"
#include "Texture.h"
#include <stdio.h>
#include <string>
#include <cstring>
#include "Buffer.h"
#include "../Utility/Debug.h"
#include "../Application/Renderer.h"

//Constructor that assigns all default values 
//------------------------------------------------------------------------------------------------------
Model::Model()
{
	isShadowMapped = 0;
	isTextured = 0;
	shininess = 0.1f;

	VAO = 0;
	EBO = 0;
	vertexVBO = 0;
	colorVBO = 0;
	normalVBO = 0;
	textureVBO = 0;
	totalVertices = 0;

	ID_vertex = 0;
	ID_normal = 0;
	ID_texture = 0;
}

Model::Model(std::string shader, std::string path, std::string texturePath)
{
	isShadowMapped = 0;
	isTextured = 0;
	shininess = 0.1f;

	VAO = 0;
	EBO = 0;
	vertexVBO = 0;
	colorVBO = 0;
	normalVBO = 0;
	textureVBO = 0;
	totalVertices = 0;

	ID_vertex = 0;
	ID_normal = 0;
	ID_texture = 0;

	unsigned int shaderID = Renderer::instance()->getShader("Default").getID();
	ID_vertex = glGetAttribLocation(shaderID, "vertex");
	ID_normal = glGetAttribLocation(shaderID, "normal");
	ID_texture = glGetAttribLocation(shaderID, "textCoord");

	Create(shader);
	loadModel(path);
	loadTexture("bricks2");
	
}

//Predicate function that returns flag reference
//------------------------------------------------------------------------------------------------------
GLint& Model::getIsTextured()
{
	return isTextured;
}

//Setter function that sets shininess value of model's material
//------------------------------------------------------------------------------------------------------
void Model::SetShininess(GLfloat shininess)
{
	this->shininess = shininess;
}
//
////Setter function that sets ambient component of model's material
////------------------------------------------------------------------------------------------------------
//void Model::SetAmbient(GLfloat r, GLfloat g, GLfloat b)
//{
//	ambient = glm::vec3(r, g, b);
//}
//
//
////Setter function that sets diffuse component of model's material
////------------------------------------------------------------------------------------------------------
//void Model::SetDiffuse(GLfloat r, GLfloat g, GLfloat b)
//{
//	diffuse = glm::vec3(r, g, b);
//}
//
////Setter function that sets specular component of model's material
////------------------------------------------------------------------------------------------------------
//void Model::SetSpecular(GLfloat r, GLfloat g, GLfloat b)
//{
//	specular = glm::vec3(r, g, b);
//}


//Setter function that sets position of model
//------------------------------------------------------------------------------------------------------
void Model::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{
	position = glm::vec3(x, y, z);
}

//Setter function that sets rotation of model
//------------------------------------------------------------------------------------------------------
void Model::SetRotation(GLfloat x, GLfloat y, GLfloat z)
{
	rotation = glm::vec3(x, y, z);
}

//Setter function that sets scale of model
//------------------------------------------------------------------------------------------------------
void Model::SetScale(GLfloat x, GLfloat y, GLfloat z)
{
	scale = glm::vec3(x, y, z);
}


//Function that loads raw model data from OBJ file 
//------------------------------------------------------------------------------------------------------
bool Model::loadObj(const std::string& filepath)
{
	std::vector <glm::vec3> m_vertices, m_normals, temp_tangent, temp_bitangent;
	std::vector <glm::vec2> m_uvs;

	std::vector <unsigned int> vertexIndices, uvIndices, normalIndices;

	std::vector<unsigned short> out_indices;
	std::vector<glm::vec3> out_vertices;
	std::vector<glm::vec2> out_uvs;
	std::vector<glm::vec3> out_normals;

	std::vector<glm::vec3> temp_vertices, temp_normals;
	std::vector<glm::vec2> temp_uvs;


	std::string temp_text = "";
	FILE* file = fopen(filepath.c_str(), "r");

	//Open File
	if (!file)
	{
		Debug::Log("Impossible to openfile", ALERT);
		return false;
	}

	//Read file until the end
	while (1)
	{
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);

		if (res == EOF)
		{
			break;
		}

		//Parse lineheader
		int x = strcmp(lineHeader, "v");
		if (strcmp(lineHeader, "v") == 0)
		{
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		//scan for uvs
		else if (strcmp(lineHeader, "vt") == 0)
		{
			glm::vec2 uv;
			glm::vec2 uv2;
			glm::vec2 uv3;
			fscanf(file, "%f %f %f %f\n", &uv.x, &uv.y, &uv3.x, &uv2.y);
			temp_uvs.push_back(uv);
		}
		//scan for normals
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		//Scan for faces
		else if (strcmp(lineHeader, "f") == 0)
		{

			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[4], uvIndex[4], normalIndex[4];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);

			if (matches != 9)
			{

				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2], &vertexIndex[3], &uvIndex[3], &normalIndex[3]);

				if (matches != 12)
				{
					printf("File can't be read : ( Try exporting with other options\n");
					fclose(file);
					return false;
				}
			}


			//triangulated
			if (matches == 9)
			{
				//Add 3 total vertices
				totalVertices += 3;

				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}
			if (matches == 12)
			{
				//Add 3 total vertices
				totalVertices += 6;
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);

				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[3]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[3]);
				uvIndices.push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[3]);
				normalIndices.push_back(normalIndex[2]);
			}
		}
	}
	std::vector<GLfloat> testVertex;
	std::vector<GLfloat> testUv;
	std::vector<GLfloat> testNormal;

	//Go through each vertex of each triangle
	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		glm::vec2 uv = temp_uvs[uvIndex - 1];
		glm::vec3 normal = temp_normals[normalIndex - 1];
		m_normals.push_back(normal);

		m_vertices.push_back(vertex);
		m_uvs.push_back(uv);
	}

	fclose(file);
	unsigned short result;

	std::vector<GLuint> tempIndices;
	std::vector<GLuint> testindices;
	std::vector<glm::vec3> indexed_vertices;
	std::vector<glm::vec2> indexed_uvs;
	std::vector<glm::vec3> indexed_normals;

	indexVBO(m_vertices, m_uvs, m_normals, tempIndices, indexed_vertices, indexed_uvs, indexed_normals);


	//Calculate tangents and bitangents of model
	CalculateTangents(m_vertices, m_uvs, m_normals, temp_tangent, temp_bitangent);
	glm::vec3 color = glm::vec3(1.0f);

	std::vector<GLfloat> testv;
	std::vector<GLfloat> testu;
	std::vector<GLfloat> testn;
	std::vector<GLfloat> testc;
	for (size_t i = 0; i < m_vertices.size(); i++)
	{
		testv.push_back(m_vertices[i].x);
		testv.push_back(m_vertices[i].y);
		testv.push_back(m_vertices[i].z);

		testu.push_back(m_uvs[i].x);
		testu.push_back(m_uvs[i].y);

		testn.push_back(m_normals[i].x);
		testn.push_back(m_normals[i].y);
		testn.push_back(m_normals[i].z);

		tangents.push_back(temp_tangent[i].x);
		tangents.push_back(temp_tangent[i].y);
		tangents.push_back(temp_tangent[i].z);

		bitangents.push_back(temp_bitangent[i].x);
		bitangents.push_back(temp_bitangent[i].y);
		bitangents.push_back(temp_bitangent[i].z);

		testc.push_back(color.x);
		testc.push_back(color.y);
		testc.push_back(color.z);

		testindices.push_back(i);
	}
	indices = testindices;
	vertices = testv;
	//Bind all VBOs and shader attributes together with VAO
	//Bind all VBOs and shader attributes together with VAO
	//Bind all VBOs and shader attributes together with VAO
	glBindVertexArray(VAO);
	//fFll and link vertex VBO
	buffer->BindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	buffer->FillBuffer(GL_ARRAY_BUFFER, testv, GL_STATIC_DRAW);
	buffer->LinkToShader(ID_vertex, 3, GL_FLOAT, GL_FALSE, 0, 0);
	buffer->EnableVertexArray(ID_vertex);

	//Fill and link normal VBO
	buffer->BindBuffer(GL_ARRAY_BUFFER, normalVBO);
	buffer->FillBuffer(GL_ARRAY_BUFFER, testn, GL_STATIC_DRAW);
	buffer->LinkToShader(ID_normal, 3, GL_FLOAT, GL_FALSE, 0, 0);
	buffer->EnableVertexArray(ID_normal);

	//Fill and link texture VBO
	buffer->BindBuffer(GL_ARRAY_BUFFER, textureVBO);
	buffer->FillBuffer(GL_ARRAY_BUFFER, testu, GL_STATIC_DRAW);
	buffer->LinkToShader(ID_texture, 2, GL_FLOAT, GL_FALSE, 0, 0);
	buffer->EnableVertexArray(ID_texture);

	//Fill EBO with indices 
	buffer->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	buffer->FillBuffer(GL_ELEMENT_ARRAY_BUFFER, tempIndices.size() * sizeof(GLuint), &tempIndices[0], GL_STATIC_DRAW);

	if (isNormalMapped == 1)
	{
		////Fill and link texture VBO
		//buffer->GenerateBuffers(1, &VBO_tangent);
		//buffer->BindBuffer(GL_ARRAY_BUFFER, VBO_tangent);
		//buffer->FillBuffer(GL_ARRAY_BUFFER, tangents, GL_STATIC_DRAW);
		//buffer->LinkToShader(ID_tangent, 3, GL_FLOAT, GL_FALSE, 0, 0);
		//buffer->EnableVertexArray(ID_tangent);

		//if (isHeightMapped)
		//{
		//	buffer->GenerateBuffers(1, &VBO_bitangent);
		//	buffer->BindBuffer(GL_ARRAY_BUFFER, VBO_bitangent);
		//	buffer->FillBuffer(GL_ARRAY_BUFFER, bitangents, GL_STATIC_DRAW);
		//	buffer->LinkToShader(ID_bitangent, 3, GL_FLOAT, GL_FALSE, 0, 0);
		//	buffer->EnableVertexArray(ID_bitangent);
		//}
	}
	//Fill EBO with indices 
	//buffer->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //gl bind buffer
	//buffer->FillBuffer(GL_ELEMENT_ARRAY_BUFFER, testindices.size() * sizeof(GLuint), &testindices[0], GL_STATIC_DRAW); //gl buffer data

	glBindVertexArray(0);

	return true;
}

bool Model::is_near(float v1, float v2) {
	return fabs(v1 - v2) < 0.01f;
}
struct PackedVertex {
	glm::vec3 position;
	glm::vec2 uv;
	glm::vec3 normal;
	bool operator<(const PackedVertex that) const {
		return memcmp((void*)this, (void*)&that, sizeof(PackedVertex)) > 0;
	};
};
bool getSimilarVertexIndex_fast(
	PackedVertex& packed,
	std::map<PackedVertex, unsigned short>& VertexToOutIndex,
	unsigned short& result
) {
	std::map<PackedVertex, unsigned short>::iterator it = VertexToOutIndex.find(packed);
	if (it == VertexToOutIndex.end()) {
		return false;
	}
	else {
		result = it->second;
		return true;
	}
}
// Searches through all already-exported vertices
// for a similar one.
// Similar = same position + same UVs + same normal
bool Model::getSimilarVertexIndex(glm::vec3& in_vertex, glm::vec2& in_uv, glm::vec3& in_normal, std::vector<glm::vec3>& out_vertices, std::vector<glm::vec2>& out_uvs, std::vector<glm::vec3>& out_normals, unsigned short& result)
{
	// Lame linear search
	for (unsigned int i = 0; i < out_vertices.size(); i++)
	{
		if (
			is_near(in_vertex.x, out_vertices[i].x) &&
			is_near(in_vertex.y, out_vertices[i].y) &&
			is_near(in_vertex.z, out_vertices[i].z) &&
			is_near(in_uv.x, out_uvs[i].x) &&
			is_near(in_uv.y, out_uvs[i].y) &&
			is_near(in_normal.x, out_normals[i].x) &&
			is_near(in_normal.y, out_normals[i].y) &&
			is_near(in_normal.z, out_normals[i].z)
			)
		{
			result = i;
			return true;
		}
	}

	// No other vertex could be used instead.
	// Needs to be added to VBO
	return false;
}

void Model::indexVBO_slow(
	std::vector<glm::vec3>& in_vertices,
	std::vector<glm::vec2>& in_uvs,
	std::vector<glm::vec3>& in_normals,

	std::vector<unsigned short>& out_indices,
	std::vector<glm::vec3>& out_vertices,
	std::vector<glm::vec2>& out_uvs,
	std::vector<glm::vec3>& out_normals
) {
	// For each input vertex
	for (unsigned int i = 0; i < in_vertices.size(); i++) {

		// Try to find a similar vertex in out_XXXX
		unsigned short index;
		bool found = getSimilarVertexIndex(in_vertices[i], in_uvs[i], in_normals[i], out_vertices, out_uvs, out_normals, index);

		if (found) { // A similar vertex is already in the VBO, use it instead !
			out_indices.push_back(index);
		}
		else { // If not, it needs to be added in the output data.
			out_vertices.push_back(in_vertices[i]);
			out_uvs.push_back(in_uvs[i]);
			out_normals.push_back(in_normals[i]);
			out_indices.push_back((unsigned short)out_vertices.size() - 1);
		}
	}
}
void Model::indexVBO(std::vector<glm::vec3>& in_vertices, std::vector<glm::vec2>& in_uvs, std::vector<glm::vec3>& in_normals, std::vector<GLuint>& out_indices, std::vector<glm::vec3>& out_vertices, std::vector<glm::vec2>& out_uvs, std::vector<glm::vec3>& out_normals)
{
	std::map<PackedVertex, unsigned short> VertexToOutIndex;

	// For each input vertex
	for (unsigned int i = 0; i < in_vertices.size(); i++) {

		PackedVertex packed = { in_vertices[i], in_uvs[i], in_normals[i] };


		// Try to find a similar vertex in out_XXXX
		unsigned short index;
		bool found = getSimilarVertexIndex_fast(packed, VertexToOutIndex, index);

		if (found) { // A similar vertex is already in the VBO, use it instead !
			out_indices.push_back(index);
		}
		else { // If not, it needs to be added in the output data.
			out_vertices.push_back(in_vertices[i]);
			out_uvs.push_back(in_uvs[i]);
			out_normals.push_back(in_normals[i]);
			unsigned short newindex = (unsigned short)out_vertices.size() - 1;
			out_indices.push_back(newindex);
			VertexToOutIndex[packed] = newindex;
		}
	}
}

//Calculate Tangents
//------------------------------------------------------------------------------------------------------
void Model::CalculateTangents(// inputs
	std::vector<glm::vec3>& vertices,
	std::vector<glm::vec2>& uvs,
	std::vector<glm::vec3>& normals,
	// outputs
	std::vector<glm::vec3>& tangents,
	std::vector<glm::vec3>& bitangents)
{

	for (unsigned int i = 0; i < vertices.size(); i += 3) {

		// Shortcuts for vertices
		glm::vec3& v0 = vertices[i + 0];
		glm::vec3& v1 = vertices[i + 1];
		glm::vec3& v2 = vertices[i + 2];

		// Shortcuts for UVs
		glm::vec2& uv0 = uvs[i + 0];
		glm::vec2& uv1 = uvs[i + 1];
		glm::vec2& uv2 = uvs[i + 2];

		// Edges of the triangle : postion delta
		glm::vec3 deltaPos1 = v1 - v0;
		glm::vec3 deltaPos2 = v2 - v0;

		// UV delta
		glm::vec2 deltaUV1 = uv1 - uv0;
		glm::vec2 deltaUV2 = uv2 - uv0;

		float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
		glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
		glm::vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;

		// Set the same tangent for all three vertices of the triangle.
		// They will be merged later, in vboindexer.cpp
		tangents.push_back(tangent);
		tangents.push_back(tangent);
		tangents.push_back(tangent);

		// Same thing for binormals
		bitangents.push_back(bitangent);
		bitangents.push_back(bitangent);
		bitangents.push_back(bitangent);

	}

	// See "Going Further"
	for (unsigned int i = 0; i < vertices.size(); i += 1)
	{
		glm::vec3& n = normals[i];
		glm::vec3& t = tangents[i];
		glm::vec3& b = bitangents[i];

		// Gram-Schmidt orthogonalize
		t = glm::normalize(t - n * glm::dot(n, t));

		// Calculate handedness
		if (glm::dot(glm::cross(n, t), b) < 0.0f) {
			t = t * -1.0f;
		}
	}
}

//Function that loads raw model data from OBJ file 
//------------------------------------------------------------------------------------------------------
bool Model::loadModel(const std::string& filename)
{
	firstML = true;
	//Variables to load and store all model data
	std::fstream file;
	std::string lineText = "";
	unsigned int tokenPosition = 0;

	std::vector<glm::vec3> faceArray;
	std::vector<glm::vec3> vertexArray;
	std::vector<glm::vec2> textureArray;
	std::vector<glm::vec3> normalArray;

	std::vector<std::string> subNumbers;
	std::vector<std::string> subStrings;

	//Display text to state that file is being opened and read
	std::cout << "Opening and reading model file : " << "\"" << filename << "\"" << std::endl;

	//Open model file
	file.open(filename);

	//If opening of model file failed, display error message
	if (!file)
	{
		Debug::Log("File could not be loaded.", ALERT);
		return false;
	}

	//Read in all model data until end of file is reached
	while (!file.eof())
	{

		//Read line of text
		getline(file, lineText);

		//Break text string into smaller substrings
		do
		{
			tokenPosition = lineText.find(' ');
			subStrings.push_back(lineText.substr(0, tokenPosition));
			lineText.erase(0, tokenPosition + 1);
		} while (tokenPosition != std::string::npos);

		//If first token is "v" or "vn", set the vertices and normal values
		if (subStrings[0] == "v" || subStrings[0] == "vn")
		{

			//If it's a vertex position, add it to the vertex array
			if (subStrings[0] == "v")
			{
				vertexArray.push_back(glm::vec3((GLfloat)(atof(subStrings[1].c_str())),
					(GLfloat)(atof(subStrings[2].c_str())),
					(GLfloat)(atof(subStrings[3].c_str()))));
			}

			//If it's a normal direction, add it to the normal array
			if (subStrings[0] == "vn")
			{
				normalArray.push_back(glm::vec3((GLfloat)(atof(subStrings[1].c_str())),
					(GLfloat)(atof(subStrings[2].c_str())),
					(GLfloat)(atof(subStrings[3].c_str()))));
			}

		}

		//If first token is "vt", set the UV data
		if (subStrings[0] == "vt")
		{

			//Add to the textureArray
			textureArray.push_back(glm::vec2((GLfloat)(atof(subStrings[1].c_str())),
				(GLfloat)(atof(subStrings[2].c_str()))));

		}

		//If first token is "f", create a new face and set the face data
		if (subStrings[0] == "f")
		{

			//Loop through all three face sub strings 
			for (int i = 1; i <= 3; i++)
			{

				//Break each face substring into three face numeric values
				do
				{
					tokenPosition = subStrings[i].find('/');
					subNumbers.push_back(subStrings[i].substr(0, tokenPosition));
					subStrings[i].erase(0, tokenPosition + 1);
				} while (tokenPosition != std::string::npos);

				//Add to face array
				faceArray.push_back(glm::vec3(atoi(subNumbers[0].c_str()) - 1,
					atoi(subNumbers[1].c_str()) - 1,
					atoi(subNumbers[2].c_str()) - 1));

				//Clear numbers for next use
				subNumbers.clear();

			}

		}

		//clear the sub strings for next use
		subStrings.clear();

	}

	//Close model file
	file.close();

	//Display text to state that file has been opened and read
	Debug::Log("File opened and read successfully.", SUCCESS);

	//Sift through all data for EBO
	//---------------------------------

	std::vector<GLuint> tempIndices;
	std::vector<Groups> groups;

	//Loop through all triangle faces and individually build vertex groups out of them
	//Then add each vertex group to the array but first check if it's already there and
	//Of it is then skip it but mark EBO to point to that existing index
	//This alleviates the problem of creating a EBO out of OBJ model file data
	for (size_t i = 0; i < faceArray.size(); i++)
	{

		//Create a temporary group
		Groups tri;
		tri.vertex = vertexArray[(const unsigned int)faceArray[i].x];
		tri.texture = textureArray[(const unsigned int)faceArray[i].y];
		tri.normal = normalArray[(const unsigned int)faceArray[i].z];

		//Flag for element found
		bool isFound = false;

		//Set below for-loop starting point to always go 5 elements back
		//So that we don't loop through entire group array each time
		int loopStart = (groups.size() >= 5 ? groups.size() - 5 : 0);

		//Loop through existing groups to see if this group already exists in there
		//And if its found use that index for the EBO otherwise continue searching
		for (size_t j = loopStart; j < groups.size(); j++)
		{

			if (tri.vertex == groups[j].vertex &&
				tri.texture == groups[j].texture &&
				tri.normal == groups[j].normal)
			{
				tempIndices.push_back(j);
				isFound = true;
				break;
			}

		}

		//If nothing was found, it's a new group so add it and index the EBO
		if (!isFound)
		{
			groups.push_back(tri);
			tempIndices.push_back(groups.size() - 1);
		}
	}

	//Stats for vertices saved
	std::cout << "Total Vertices : " << tempIndices.size() << std::endl;
	std::cout << "Actual Vertices : " << groups.size() << std::endl;
	std::cout << "Vertex Space Saved : "
		<< 100 - (int)((float)(groups.size()) / (float)(tempIndices.size()) * 100) << "%" << std::endl;

	//---------------------------------
	//Add all data to VBOs
	//---------------------------------

	//Storage for our vertex, texture and normal data
	std::vector<GLfloat> tempVertices;
	std::vector<GLfloat> tempTextures;
	std::vector<GLfloat> tempNormals;

	//Add all vertex, texture and normal data to the main vectors
	//From here this data will be fed into to VBO later on
	for (size_t j = 0; j < groups.size(); j++)
	{

		tempVertices.push_back(groups[j].vertex.x);
		tempVertices.push_back(groups[j].vertex.y);
		tempVertices.push_back(groups[j].vertex.z);

		tempTextures.push_back(groups[j].texture.s);
		tempTextures.push_back(groups[j].texture.t);

		tempNormals.push_back(groups[j].normal.x);
		tempNormals.push_back(groups[j].normal.y);
		tempNormals.push_back(groups[j].normal.z);

	}

	//Total up vertices for use in Draw() function
	totalVertices = tempIndices.size();

	/*std::vector<GLfloat> testv;
	std::vector<GLfloat> testu;
	std::vector<GLfloat> testn;
	std::vector<unsigned int> testi;

	Debug::Log("size + " + std::to_string(vertices.size()), LOG);

	for (size_t i = 0; i < vertices.size(); i++)
	{
		testv.push_back(vertices[i].x);
		testv.push_back(vertices[i].y);
		testv.push_back(vertices[i].z);

		testu.push_back(uvs[i].x);
		testu.push_back(uvs[i].y);

		testn.push_back(normals[i].x);
		testn.push_back(normals[i].y);
		testn.push_back(normals[i].z);

		testi.push_back(indices[i]);
	}*/

	//Bind all VBOs and shader attributes together with VAO
	glBindVertexArray(VAO);
	//fFll and link vertex VBO
	buffer->BindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	buffer->FillBuffer(GL_ARRAY_BUFFER, tempVertices, GL_STATIC_DRAW);
	buffer->LinkToShader(ID_vertex, 3, GL_FLOAT, GL_FALSE, 0, 0);
	buffer->EnableVertexArray(ID_vertex);

	//Fill and link normal VBO
	buffer->BindBuffer(GL_ARRAY_BUFFER, normalVBO);
	buffer->FillBuffer(GL_ARRAY_BUFFER, tempNormals, GL_STATIC_DRAW);
	buffer->LinkToShader(ID_normal, 3, GL_FLOAT, GL_FALSE, 0, 0);
	buffer->EnableVertexArray(ID_normal);

	//Fill and link texture VBO
	buffer->BindBuffer(GL_ARRAY_BUFFER, textureVBO);
	buffer->FillBuffer(GL_ARRAY_BUFFER, tempTextures, GL_STATIC_DRAW);
	buffer->LinkToShader(ID_texture, 2, GL_FLOAT, GL_FALSE, 0, 0);
	buffer->EnableVertexArray(ID_texture);

	//Fill EBO with indices 
	buffer->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	buffer->FillBuffer(GL_ELEMENT_ARRAY_BUFFER, tempIndices.size() * sizeof(GLuint), &tempIndices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);

	return true;

}

//Function that loads in texture file for model
//------------------------------------------------------------------------------------------------------
bool Model::loadTexture(const std::string& filename)
{
	isTextured = 1;

	return Renderer::instance()->getMat("Default")->getAmbientTexture()->loadTexture(filename);
}

//Function that unloads texture file for model
//------------------------------------------------------------------------------------------------------
//void Model::UnloadTexture(const std::string textureID)
//{
//	isTextured = 0;
//
//	texture.Unload(textureID);
//}

//Load Normal Map
//------------------------------------------------------------------------------------------------------
//void Model::LoadNormalMap(std::string filepath)
//{
//	isNormalMapped = 1;
//	std::string tempSave = filepath;
//	std::vector<std::string> tempVec;
//	char tempToken = '/';
//	ParseText(tempSave, tempToken, tempVec);
//	normalMap.Load(filepath, tempVec[1]);
//}

//Load Height Map
//------------------------------------------------------------------------------------------------------
//void Model::LoadHeightMap(std::string filepath)
//{
//	isHeightMapped = 1;
//	std::string tempSave = filepath;
//	std::vector<std::string> tempVec;
//	char tempToken = '/';
//	ParseText(tempSave, tempToken, tempVec);
//	heightMap.Load(filepath, tempVec[1]);
//}

//Function that creates and fills all buffers with vertex and color data 
//------------------------------------------------------------------------------------------------------
void Model::Create(std::string programString)
{
	//Set program string to classe's
	shader = programString;

	//Set material color to default
	shininess = 1.0f;

	//Get all other shader IDs relating to attributes

	ID_vertex = 0;
	ID_normal = 1;
	ID_texture = 2;
	ID_tangent = 3;
	ID_bitangent = 4;

	//Create VAO, VBOs and EBO
	buffer->GenerateVertexArrays(1, &VAO);
	buffer->GenerateBuffers(1, &vertexVBO);
	buffer->GenerateBuffers(1, &colorVBO);
	buffer->GenerateBuffers(1, &normalVBO);
	buffer->GenerateBuffers(1, &textureVBO);
	buffer->GenerateBuffers(1, &EBO);
}
//------------------------------------------------------------------------------------------------------
//Function that adjusts model's transformations
//------------------------------------------------------------------------------------------------------
void Model::Update()
{


}
//------------------------------------------------------------------------------------------------------
//Function that renders model on screen
//------------------------------------------------------------------------------------------------------
void Model::draw()
{
	Renderer::instance()->getShader(shader).Use();
	//Renderer::instance()->getShader("Default").setUniform("skybox", 0);

	//Only if model is set to be textured bind the texture
	//if (isTextured == 1)
	//{
	//	glActiveTexture(GL_TEXTURE0);
	//	mat->getAmbientTexture()->bind();

	//	if (isNormalMapped == 1)
	//	{
	//		//Bind Normal Mapping
	//		glActiveTexture(GL_TEXTURE1);

	//		mat->getNormalMap()->bind();

	//		if (isHeightMapped == 1)
	//		{
	//			//Bind Height Mapping
	//			glActiveTexture(GL_TEXTURE2);

	//			mat->getHeightMap()->bind();
	//		}
	//	}
	//}

	//Bind VAO and render everything!
	glBindVertexArray(VAO);

	if (firstML)
	{
		//glDrawArrays(GL_TRIANGLES, totalVertices, GL_UNSIGNED_INT);
		glDrawElements(GL_TRIANGLES, totalVertices, GL_UNSIGNED_INT, 0);
	}
	else
	{
		//glDrawArrays(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	}

	glBindVertexArray(0);

}
//------------------------------------------------------------------------------------------------------
//Function that destroys all buffer objects
//------------------------------------------------------------------------------------------------------
void Model::Destroy()
{

	//destroy EBO, VBOs and VAO
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &textureVBO);
	glDeleteBuffers(1, &normalVBO);
	glDeleteBuffers(1, &colorVBO);
	glDeleteBuffers(1, &vertexVBO);
	glDeleteVertexArrays(1, &VAO);

}