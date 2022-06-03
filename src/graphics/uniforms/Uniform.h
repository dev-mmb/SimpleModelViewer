#pragma once

#include <glew.h>
#include <string>

/**
 * \brief Uniforms should always be heap allocated!!!
 */
class Uniform
{
public:
	virtual ~Uniform() {};
	Uniform(std::string name);

	void compile(GLuint shaderId);

	void unBind();

	virtual void renderUI() {}
	virtual void bind() {}
	std::string getName() const { return this->name; }

protected:
	GLuint location;
	std::string name;

	std::string getNameWithoutMaterialName() const
	{
		size_t p = name.find('.');
		if (p == std::string::npos) return name;
		return name.substr(p + 1);
	}
};

