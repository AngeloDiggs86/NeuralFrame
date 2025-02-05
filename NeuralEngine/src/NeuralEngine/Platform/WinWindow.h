#pragma once 
#include "NeuralEngine/Window.h"  // Include the base Window class header

// Includes for Event System
#include "NeuralEngine/Event/ApplicationEvent.h" 
#include "NeuralEngine/Event/KeyEvent.h"  
#include "NeuralEngine/Event/MouseEvent.h"  

#include "GLFW/glfw3.h"
namespace NeuralEngine
{
	// WinWindow is a platform-specific implementation of the Window class using GLFW
	class WinWindow : public Window
	{
	public:
		// Constructor that takes window properties for initialization
		WinWindow(const WindowProperties& WinProp);

		// Destructor to clean up and release resources
		virtual ~WinWindow();

		// Initialize the window with given properties (overrides base class method)
		bool Init(const WindowProperties& WinProp) override;

		// Check if the window should close (overrides base class method)
		bool ShouldClose() const override;

		// Poll for events (keyboard, mouse, etc.) and swap buffers for rendering
		void PollEvents() override;

		// Swap the front and back buffers for rendering
		void SwapBuffers() override;

		// Shut down the window (e.g., destroy GLFW window)
		void ShutDown() override;

		// Get the width of the window
		unsigned int GetWidth() const override {
			return m_data.width;
		}

		// Get the height of the window
		unsigned int GetHeight() const override {
			return m_data.height;
		}

		// Set the event callback function to handle window events
		void SetEventCallBack(const EventCallBackFn& callback) override
		{
			m_data.callback = callback;  // Store the callback function in window data
		}

	private:
		// Pointer to the GLFW window
		GLFWwindow* m_Window;

		// Structure to store window data (title, width, height, and callback)
		struct WindowData
		{
			std::string title = "";  // Window title
			unsigned int width = 0, height = 0;  // Window dimensions (width, height)
			EventCallBackFn callback = EventCallBackFn();  // Event callback function
		};

		// Instance of WindowData to store the current window properties
		WindowData m_data;
	};
}
