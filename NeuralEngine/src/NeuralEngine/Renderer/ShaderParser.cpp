#include "Enpch.h"
#include "ShaderParser.h"
#include <fstream>
#include <string>
#include <sstream>

namespace NeuralEngine
{
	ShaderProgramSource ShaderParser::ParseShader(const std::string& file)
	{
		std::ifstream stream(file);

		enum class ShaderType
		{
			NONE = -1, VERTEX = 0, FRAGMENT = 1 
		};
		std::string line;
		std::stringstream ss[2];
		ShaderType shaderType = ShaderType::NONE;
		while (getline(stream, line))
		{
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
					shaderType = ShaderType::VERTEX;
				else if (line.find("fragment") != std::string::npos)
					shaderType = ShaderType::FRAGMENT;
			}
			else
			{
				ss[(int)shaderType] << line << '\n';
			}
		}

		return { ss[0].str(), ss[1].str() };
	}
}