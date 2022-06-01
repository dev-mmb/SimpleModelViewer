#pragma once

#include <glew.h>
#include <string>

class Uniform
{
public:
	virtual ~Uniform() = default;
	Uniform(std::string name);

	void compile(GLuint shaderId);

	void unBind();

	virtual void renderUI() {}
	virtual void bind() {}
	std::string getName() { return this->name; }
protected:
	GLuint location;
	std::string name;

	std::string getNameWithoutMaterialName()
	{
		size_t p = name.find('.');
		if (p == std::string::npos) return name;
		return name.substr(p + 1);
	}
};

