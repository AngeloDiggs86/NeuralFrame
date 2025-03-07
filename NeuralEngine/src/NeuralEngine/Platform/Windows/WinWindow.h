#pragma once 
#include "NeuralEngine/Window.h"  // Include the base Window class header

// Includes for Event System
#include "NeuralEngine/Event/ApplicationEvent.h" 
#include "NeuralEngine/Event/KeyEvent.h"  
#include "NeuralEngine/Event/MouseEvent.h"  

#include "GLFW/glfw3.h"
#include "NeuralEngine/Platform/OpenGL/OpenGLContext.h"

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

		virtual void SwapBuffer() override;

		// Initialize the window with given properties (overrides base class method)
		bool Init(const WindowProperties& WinProp) override;

		// Shut down the window (e.g., destroy GLFW window)
		void ShutDown() override;

		void OnUpdate() override;

		inline void SetVSync(bool enabled) override;

		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const { return m_Window; }

		// Get the width of the window
		unsigned int GetWidth() const override {
			return m_data.width;
		}

		// Get the height of the window
		unsigned int GetHeight() const override {
			return m_data.height;
		}

		// Set the event callback function to handle window events
		void SetEventCallBack(const EventCallbackFn& callback) override
		{
			m_data.callback = callback;  // Store the callback function in window data
		}

	private:
		// Pointer to the GLFW window
		GLFWwindow* m_Window;

		GraphicsContext* m_Context;
		// Structure to store window data (title, width, height, and callback)
		struct WindowData
		{
			std::string title = "";  // Window title
			unsigned int width = 0, height = 0;  // Window dimensions (width, height)
			bool VSync;
			EventCallbackFn callback = EventCallbackFn();  // Event callback function
		};

		// Instance of WindowData to store the current window properties
		WindowData m_data;
	};
}
