#include "Enpch.h"  // Precompiled header for faster compilation
#include "Application.h"  // Include the header for the Application class
#include "NeuralEngine/Log.h"  // Include the logging system

#include "Event/MouseEvent.h"  // Include event classes for mouse events
// Macro to bind events to the appropriate member function of Application class
# define BIND_EVENT(X) std::bind(&Application::X, this, std::placeholders::_1)

#include "glad/glad.h"

namespace NeuralEngine
{
	// The Application class is the main entry point and controller for the engine
	Application::Application()
	{
		// Create the window and store it in m_Window
		m_Window = std::unique_ptr<Window>(Window::Create());

		// Set the event callback to the OnEvent method of Application
		m_Window->SetEventCallBack(BIND_EVENT(OnEvent));

		unsigned int id;
		glGenVertexArrays(1,&id);
	}

	// Destructor for the Application class
	Application::~Application()
	{
		// Clean up resources here if necessary
	}

	// Handle events passed to the application
	void Application::OnEvent(Event& e)
	{
		// Create an event dispatcher to handle events
		EventDispatcher dispatcher(e);

		// Dispatch the WindowCloseEvent to the OnWindowClose method
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT(OnWindowClose));

		// Process the event through all layers in the layer stack
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);  // Pass the event to each layer
			if (e.Handled)  // If the event is handled, stop further propagation
				break;
		}
	}

	// Main loop for running the application
	void Application::Run()
	{
		// The application continues running while m_Running is true
		while (m_Running)
		{
			// Set the clear color to purple and clear the color buffer
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			// Poll events (e.g., keyboard, mouse) for the window
			m_Window->PollEvents();

			// Update all layers in the layer stack
			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();  // Update each layer
			}
		}
	}

	// Method to handle the WindowCloseEvent, sets m_Running to false to exit the application
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;  // Stop the application
		return m_Running;
	}

	// Push a layer onto the layer stack (layers are rendered in order)
	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	// Push an overlay layer onto the layer stack (overlays are rendered on top of layers)
	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}
}
