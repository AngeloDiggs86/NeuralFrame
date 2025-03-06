#include "NeuralEngine.h"

class ExampleLayer : public NeuralEngine::Layer
{
public:
	ExampleLayer() :
		Layer("Layer Example") {}

	void OnUpdate() override
	{
		if(NeuralEngine::Input::IsKeyPressed(NE_KEY_TAB))
			NE_CLIENT_INFO("Tab key is pressed!");
	}

	void OnEvent(NeuralEngine::Event& event) override
	{
		//NE_CLIENT_TRACE("{0}", event);
	}
};

class SandBox : public NeuralEngine::Application
{
public:

	SandBox()
	{
		PushLayer(new ExampleLayer());
	}

	~SandBox()
	{

	}
};

NeuralEngine::Application* NeuralEngine::CreateApplication()
{
	return new SandBox();
}