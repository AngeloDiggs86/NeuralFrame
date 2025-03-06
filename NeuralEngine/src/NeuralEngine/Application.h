#pragma once 
#include "NeuralEngineCore.h"  // Include the core engine header
#include "LayerStack.h"  // Include the header for managing layer stack
#include "Window.h"  // Include the window management header
#include "Event/ApplicationEvent.h"  // Include application-related event classes
#include "NeuralEngine/ImGui/ImGuiLayer.h"

namespace NeuralEngine
{
	// The Application class is the core of the engine, handling window creation, event processing, and running the main loop
	class NEURAL_ENGINE_API Application
	{
	public:
		// Constructor for the Application class, initializes window and other systems
		Application();

		// Destructor for the Application class, cleans up resources
		virtual ~Application();

		// Handles events and dispatches them to appropriate functions
		virtual void OnEvent(Event& e);

		// Handles window close events specifically
		virtual bool OnWindowClose(WindowCloseEvent& e);

		// Push a layer to the stack, layers will be rendered in order
		void PushLayer(Layer* layer);

		// Push an overlay layer to the stack, overlays are rendered on top of layers
		void PushOverlay(Layer* overlay);

		// Main loop to run the application
		void Run();

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }

	private:
		// Pointer to the window object, unique pointer ensures automatic memory management
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		// Flag to track if the application is running
		bool m_Running = true;

		// Layer stack to manage and update all layers in the application
		LayerStack m_LayerStack;

		static Application* s_Instance;
	};

	// To be defined in the client code, used to create the application instance
	Application* CreateApplication();
}
