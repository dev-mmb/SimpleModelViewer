#include "ShaderProgram.h"

#include <fstream>
#include <sstream>
#include <string>
#include <string_view>

#include <glm/gtc/type_ptr.hpp>

#include "glsl_type_set.h"
#include "../uniforms/Uniform1f.h"
#include "../uniforms/Uniform3f.h"
#include "../uniforms/Uniform1i.h"
#include "../uniforms/UniformMat4.h"
#include "../uniforms/UniformSampler2D.h"

ShaderProgram::ShaderProgram()
	: id(0)
{}

ShaderProgram::~ShaderProgram()
{
	if (id != 0)
	{
		glDeleteProgram(id);
		id = 0;
	}
	uniforms.clear();
}

void ShaderProgram::createFromString(const std::string& vertexShader, const std::string& fragmentShader)
{
	compileShader(vertexShader, fragmentShader);
}

void ShaderProgram::createFromFile(const std::string& vertexShaderFileName, const std::string& fragmentShaderFileName)
{
	this->vertexShader = vertexShaderFileName; this->fragmentShader = fragmentShaderFileName;
	std::string vertexShader = readFile(vertexShaderFileName);
	std::string fragmentShader = readFile(fragmentShaderFileName);
	compileShader(vertexShader, fragmentShader);
}

void ShaderProgram::compile()
{
	for (auto& uniform : uniforms)
	{
		uniform->compile(id);
	}
}

void ShaderProgram::bind()
{
	glUseProgram(id);
	for (auto& uniform : uniforms)
	{
		uniform->bind();
	}
}

void ShaderProgram::unBind()
{
	glUseProgram(0);
}

std::unordered_map<std::string, int> ShaderProgram::getAllUniformsFromMaterial(const std::string& materialName) const
{
	std::unordered_map<std::string, int> uniformIds;

	for (int i = 0; i < this->uniforms.size(); i++)
	{
		auto& uniform = this->uniforms[i];
		size_t dotPos = uniform->getName().find('.');
		if (dotPos != std::string::npos)
		{
			const std::string material = uniform->getName().substr(0, dotPos);
			if (material == materialName)
			{
				uniformIds[uniform->getName().substr(uniform->getName().find('.') + 1)] = i;
			}
		}
	}

	return uniformIds;
}

void ShaderProgram::getAllUniforms()
{
	GLint count;
	GLint size; // size of the variable
	GLenum type; // type of the variable (float, vec3 or mat4, etc)
	const GLsizei bufSize = 128; // maximum name length
	GLchar namebuffer[bufSize]; // variable name in GLSL
	GLsizei length; // name length

	glGetProgramiv(id, GL_ACTIVE_UNIFORMS, &count);

	for (GLint i = 0; i < count; i++)
	{
		glGetActiveUniform(id, (GLuint)i, bufSize, &length, &size, &type, namebuffer);

		std::string name = namebuffer;
		size_t dotPos =  name.find('.');

		if (dotPos != std::string::npos)
		{
			createUniform(name, type);
		}
	}
}

void ShaderProgram::createUniform(const std::string& name, GLenum type)
{
	if (type == GL_FLOAT)
	{
		 this->uniforms.push_back(new Uniform1f(name));
	}
	else if (type == GL_FLOAT_VEC3)
	{
		this->uniforms.push_back(new Uniform3f(name));
	}
	else if (type == GL_FLOAT_MAT4)
	{
		this->uniforms.push_back(new UniformMat4(name));
	}
	else if (type == GL_INT)
	{
		this->uniforms.push_back(new Uniform1i(name));
	}
	else if (type == GL_SAMPLER_2D)
	{
		this->uniforms.push_back(new UniformSampler2D(name));
	}
	else
	{
		std::cout << "error creating uniform of type: " << type_set[type] << " with name: " << name << "\n";
	}
}


void ShaderProgram::compileShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	id = glCreateProgram();

	if (!id)
	{
		std::cout << "could not create shader\n";
		return;
	}

	addShader(id, vertexShader, GL_VERTEX_SHADER);
	addShader(id, fragmentShader, GL_FRAGMENT_SHADER);

	glLinkProgram(id);
	if (hasErrors(id)) return;


	glValidateProgram(id);
	if (hasErrors(id)) return;

	getAllUniforms();
}

void ShaderProgram::addShader(GLuint program, const std::string& code, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);
	const GLchar* theCode[1];
	theCode[0] = code.c_str();

	GLint codeLength[1];
	codeLength[0] = code.length();

	glShaderSource(shader, 1, theCode, codeLength);
	glCompileShader(shader);

	GLint result = 0;
	GLchar log[1024] = { 0 };
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(shader, sizeof(log), NULL, log);
		std::cout << "Error creating shader program" << "\n\t" << log;
	}

	glAttachShader(program, shader);
}

std::string ShaderProgram::readFile(const std::string& file)
{
	
	const std::ifstream stream(file, std::ios::in);
	std::stringstream buffer;
	buffer << stream.rdbuf();
	return buffer.str();
}

bool ShaderProgram::hasErrors(GLuint value)
{
	GLint result = 0;
	GLchar log[1024] = { 0 };

	glGetProgramiv(id, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(id, sizeof(log), NULL, log);
		std::cout << "Error validating program" << log;
		return true;
	}
	return false;
}


template <class UNIFORM_TYPE, typename VALUE_TYPE>
void ShaderProgram::setUniform(const std::string& name, VALUE_TYPE value)
{}
template<>
void ShaderProgram::setUniform<Uniform1f, float>(const std::string& name, float value)
{
	auto u = getUniformPointer(name);
	if (u == nullptr) return;
	auto castedUniform = dynamic_cast<Uniform1f*>(u);
	castedUniform->set(value);
}
template<>
void ShaderProgram::setUniform<Uniform1i, int>(const std::string& name, int value)
{
	auto u = getUniformPointer(name);
	if (u == nullptr) return;
	auto castedUniform = dynamic_cast<Uniform1i*>(u);
	castedUniform->set(value);
}
template<>
void ShaderProgram::setUniform<Uniform3f, glm::vec3>(const std::string& name, glm::vec3 value)
{
	auto u = getUniformPointer(name);
	if (u == nullptr) return;
	auto castedUniform = dynamic_cast<Uniform3f*>(u);
	castedUniform->set(value);
}
template<>
void ShaderProgram::setUniform<UniformMat4, glm::mat4>(const std::string& name, glm::mat4 value)
{
	auto u = getUniformPointer(name);
	if (u == nullptr) return;
	auto castedUniform = dynamic_cast<UniformMat4*>(u);
	castedUniform->set(value);
}