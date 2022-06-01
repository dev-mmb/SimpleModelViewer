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
	std::string vertexShader = readFile(vertexShaderFileName);
	std::string fragmentShader = readFile(fragmentShaderFileName);
	compileShader(vertexShader, fragmentShader);
}

void ShaderProgram::compile()
{
	for (Uniform* uniform : uniforms)
	{
		uniform->compile(id);
	}
}

void ShaderProgram::bind()
{
	glUseProgram(id);
	for (Uniform* uniform : uniforms)
	{
		if (uniform != nullptr)
			uniform->bind();
	}
}

void ShaderProgram::unBind()
{
	glUseProgram(0);
}

std::vector<Uniform*> ShaderProgram::getAllUniformsFromMaterial(const std::string& materialName) const
{
	std::vector<Uniform*> uniforms;
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
		size_t dotPos = name.find('.');
		if (dotPos != std::string::npos)
		{
			try
			{
				const std::string material = name.substr(0, dotPos);
				const std::string uniformName = name.substr(dotPos + 1);
				if (material == materialName)
				{
					uniforms.push_back(createUniform(name, type));
				}
			}
			catch (const std::exception& e) {
				std::cout << "Error getting uniforms for material: " << materialName << " uniform: " << name << "\n";
			}
		}
	}

	return uniforms;
}

Uniform* ShaderProgram::createUniform(const std::string& name, GLenum type) const
{
	if (type == GL_FLOAT)
	{
		return new Uniform1f(name);
	}
	else if (type == GL_FLOAT_VEC3)
	{
		return new Uniform3f(name);
	}
	else if (type == GL_FLOAT_MAT4)
	{
		return new UniformMat4(name);
	}
	else if (type == GL_INT)
	{
		return new Uniform1i(name);
	}

	std::cout << "error creating uniform of type: " << type_set[type] << " with name: " << name << "\n";
	return new Uniform(name);
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


