#include "NeuralEngine.h"

class SandBox : public NeuralEngine::Application
{
public:

	SandBox()
	{

	}

	~SandBox()
	{

	}
};

NeuralEngine::Application* NeuralEngine::CreateApplication()
{
	return new SandBox();
}