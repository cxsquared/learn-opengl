#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

class Shader
{
public:
	unsigned int ID;

	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	void use();
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setVec4(const std::string &name, float x, float y, float z, float w) const;
	void setVec3(const std::string &name, float x, float y, float z) const;
	void setVec3(const std::string &name, glm::vec3 vec) const;
	void setMat4(const std::string &name, int count, bool transpose, float* value) const;
};

#endif
