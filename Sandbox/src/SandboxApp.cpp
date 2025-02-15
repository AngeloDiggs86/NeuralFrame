#include "NeuralEngine.h"


class ExampleLayer : public NeuralEngine::Layer
{
public:
	ExampleLayer() :
		Layer("Layer Example"){ }

	void OnUpdate() override
	{
		EN_CLIENT_INFO("ExampleLayer:Update");
	}

	void OnEvent(NeuralEngine::Event& event) override
	{
		EN_CLIENT_TRACE("{0}", event);
	}
};

class SandBox : public NeuralEngine::Application
{
public:

	SandBox()
	{
		//PushLayer(new ExampleLayer);
		PushOverlay(new NeuralEngine::ImGuiLayer);
	}

	~SandBox()
	{

	}
};

NeuralEngine::Application* NeuralEngine::CreateApplication()
{
	return new SandBox();
}