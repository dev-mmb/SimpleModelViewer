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

	virtual void bind() {}
	std::string getName() { return this->name; }
protected:
	GLuint location;
	std::string name;
};

