#pragma once
#include "NeuralEngineCore.h"
#include "LayerStack.h"
#include "Window.h"
#include "Event/ApplicationEvent.h"
namespace NeuralEngine
{
	class NEURAL_ENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();
		virtual void OnEvent(Event& e);
		virtual bool OnWindowClose(WindowCloseEvent& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void Run();
		
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	//To be defined in CLIENT
	Application* CreateApplication();
}


