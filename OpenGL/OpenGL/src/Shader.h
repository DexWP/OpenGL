#pragma once

#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);

	unsigned int getID() const { return id; }

	void use();

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setMat3(const std::string& name, glm::mat3& mat33);
	void setMat4(const std::string& name, glm::mat4& mat44);
	void setVec3(const std::string& name, glm::vec3& vec);
	void setVec4(const std::string& name, glm::vec4& vec);


private:
	unsigned int id;
};

