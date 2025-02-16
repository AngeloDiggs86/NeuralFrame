#pragma once 
#include "Event/Event.h"  // Include the Event system for handling events

namespace NeuralEngine
{
	// Structure to hold window properties, such as title, width, and height
	struct WindowProperties
	{
		std::string title;  // Window title
		unsigned int width, height;  // Window dimensions (width x height)

		// Constructor to initialize window properties with default values
		WindowProperties(const std::string& _title = "Neural Engine", unsigned int _width = 1280, unsigned int _height = 720)
			:title(_title), width(_width), height(_height) {
		}
	};

	// Abstract base class that defines the essential interface for creating and managing a window
	class Window {
	public:
		// Virtual destructor to ensure proper cleanup of derived class objects
		virtual ~Window() = default;

		// Pure virtual method to initialize the window with specific properties
		virtual bool Init(const WindowProperties& WinProp) = 0;

		// Pure virtual method to check if the window should close (e.g., from user input)
		virtual bool ShouldClose() const = 0;

		// Pure virtual method to handle events like input or window events
		virtual void PollEvents() = 0;

		// Pure virtual method to swap buffers for rendering
		virtual void SwapBuffers() = 0;

		// Pure virtual method to get the window's width
		virtual unsigned int GetWidth() const = 0;

		// Pure virtual method to get the window's height
		virtual unsigned int GetHeight() const = 0;

		// Pure virtual method to shut down the window and clean up resources
		virtual void ShutDown() = 0;

		virtual void* GetNativeWindow() const = 0;

		// Type alias for the callback function signature used for event handling
		using EventCallBackFn = std::function<void(Event&)>;

		// Pure virtual method to set the callback function for handling events
		virtual void SetEventCallBack(const EventCallBackFn& callback) = 0;

		// Static factory method to create and initialize a window object
		static Window* Create(const WindowProperties& WinProp = WindowProperties());
	};
}
