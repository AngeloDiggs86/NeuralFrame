#include "Enpch.h"
#include "Application.h"
#include "NeuralEngine/Log.h" 


#include "Event/MouseEvent.h"


#include "GLFW/glfw3.h"

# define BIND_EVENT(X) std::bind(&Application::X, this, std::placeholders::_1)

namespace NeuralEngine
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallBack(BIND_EVENT(OnEvent));
	}

	Application::~Application()
	{

	}
	
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT(OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{ 
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->PollEvents();

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
		{
		m_Running = false;
		return m_Running;
		}

	void Application::PushLayer(Layer* layer)
		{
		m_LayerStack.PushLayer(layer);
		}
	
	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}
}