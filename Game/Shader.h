#ifndef SHADER_H
#define SHADER_H

#include <glm/glm.hpp>
#include <map>
#include <string>
class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
	~Shader();

	void CreateShader(const char* vertexShader, const char* fragmentShader);
	void CreateShader(const char* vertexShader, const char* geometryShader, const char* fragmentShader);

	void Use();
	void Unuse();

public:

	void SetUniform(const std::string& name, int value);
	void SetUniform(const std::string& name, float value);
	void SetUniform(const std::string& name, float x, float y);
	void SetUniform(const std::string& name, float x, float y, float z);
	void SetUniform(const std::string& name, float x, float y, float z, float w);
	void SetUniform(const std::string& name, const glm::vec2& vector);
	void SetUniform(const std::string& name, const glm::vec3& vector);
	void SetUniform(const std::string& name, const glm::vec4& vector);
	void SetUniform(const std::string& name, const glm::mat4& matrix);
	
private:

	void checkCompileErrors(GLuint shader, std::string type);

private:

	unsigned int ID;
};
#endif // !SHADER_h

