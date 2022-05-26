#ifndef SHADER_H
#define SHADER_H

#include <glm/glm.hpp>
#include <map>
#include <string>
class Shader
{
	public:
	Shader();
	~Shader();

	void CreateShader(const char* vertexShader, const char* fragmentShader);
	void CreateShader(const char* vertexShader, const char* geometryShader, const char* fragmentShader);

	void Use();
	void Unuse();

	void SetUniform(const char* name, int value);
	void SetUniform(const char* name, float value);
	void SetUniform(const char* name, float x, float y);
	void SetUniform(const char* name, float x, float y, float z);
	void SetUniform(const char* name, float x, float y, float z, float w);
	void SetUniform(const char* name, const glm::vec2& vector);
	void SetUniform(const char* name, const glm::vec3& vector);
	void SetUniform(const char* name, const glm::vec4& vector);
	void SetUniform(const char* name, const glm::mat4& matrix);

	static std::map<std::string, Shader>* s_shaderMap;
};
#endif // !SHADER_h

