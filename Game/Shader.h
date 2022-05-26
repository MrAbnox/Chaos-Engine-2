#ifndef SHADER_H
#define SHADER_H

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <map>
#include <string>
class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
	~Shader();

	void Use();

public:

	void setUniform(const std::string& name, bool value) const;
	void setUniform(const std::string& name, int value) const;
	void setUniform(const std::string& name, float value) const;
	void setUniform(const std::string& name, float x, float y) const;
	void setUniform(const std::string& name, float x, float y, float z) const;
	void setUniform(const std::string& name, float x, float y, float z, float w) const;
	void setUniform(const std::string& name, const glm::vec2& vector) const;
	void setUniform(const std::string& name, const glm::vec3& vector) const;
	void setUniform(const std::string& name, const glm::vec4& vector) const;
	void setUniform(const std::string& name, const glm::mat2& matrix) const;
	void setUniform(const std::string& name, const glm::mat3& matrix) const;
	void setUniform(const std::string& name, const glm::mat4& matrix) const;
	


	void checkCompileErrors(GLuint shader, std::string type);

private:

	unsigned int ID;
};
#endif // !SHADER_h

