#pragma once
#include "Uniform.h"

class Uniform1i : public Uniform
{
public:
	Uniform1i(const std::string& n)
		: Uniform(n), value(0)
	{}

	void set(int v);

	void bind() override;
private:
	int value;
};

