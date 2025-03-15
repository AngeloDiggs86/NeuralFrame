#pragma once
#include "iostream"

namespace NeuralEngine
{
	struct ShaderProgramSource
	{
		std::string VertexSource;
		std::string FragmentSource;
	};

	class ShaderParser
	{
	public:
		static ShaderProgramSource ParseShader(const std::string& file);
	};
}