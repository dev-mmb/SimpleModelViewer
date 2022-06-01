#pragma once
#include "Uniform.h"

class Uniform1f : public Uniform
{
public:
	Uniform1f(const std::string& n)
		: Uniform(n), value(0)
	{}
	void set(float v);

	void bind() override;
private:
	float value;
};

