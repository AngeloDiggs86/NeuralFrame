#include "Enpch.h"  // Include precompiled header for faster compilation
#include "WinWindow.h"  // Include window class header for platform-specific window handling

namespace NeuralEngine
{
	// Static variable to track if GLFW has been initialized
	static bool s_GLFWInitialized = false;

	// Destructor to clean up resources by shutting down the window
	WinWindow::~WinWindow() {
		ShutDown();
	}

	// Initialize the window with specified properties
	bool WinWindow::Init(const WindowProperties& WinProp)
	{
		// Set window properties from the passed-in WindowProperties struct
		m_data.title = WinProp.title;
		m_data.width = WinProp.width;
		m_data.height = WinProp.height;

		// Log window details to the console
		EN_CORE_INFO("Window Details: {0} , {1} , {2}", m_data.title, m_data.width, m_data.height);

		// Initialize GLFW if not already initialized
		if (!s_GLFWInitialized)
		{
			glfwInit();  // Initialize the GLFW library
			s_GLFWInitialized = true;  // Mark GLFW as initialized
		}

		// Create a window with the specified dimensions and title
		m_Window = glfwCreateWindow((int)m_data.width, (int)m_data.height, m_data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);  // Set the current context for OpenGL rendering
		glfwSetWindowUserPointer(m_Window, &m_data);  // Associate the window data with the GLFW window
		glfwSwapInterval(1);  // Enable V-Sync (swap buffers every frame)

		// Set callback for window resizing
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				// Retrieve window data and update its dimensions
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.width = width;
				data.height = height;

				// Trigger the window resize event and call the associated callback
				WindowResizeEvent event(width, height);
				data.callback(event);
			});

		// Set callback for window close event
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			// Retrieve window data and trigger the window close event
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.callback(event);
			});

		// Set callback for key press, release, and repeat events
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			// Retrieve window data and handle different key actions
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
			case GLFW_PRESS:  // Key press event
			{
				KeyPressedEvent event(key, false);
				data.callback(event);
				break;
			}
			case GLFW_RELEASE:  // Key release event
			{
				KeyReleasedEvent event(key);
				data.callback(event);
				break;
			}
			case GLFW_REPEAT:  // Key repeat event
			{
				KeyPressedEvent event(key, true);
				data.callback(event);
				break;
			}
			default:
				break;
			}
			});

		// Set callback for mouse button press and release events
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				// Retrieve window data and handle mouse button actions
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case  GLFW_PRESS:  // Mouse button press event
				{
					MouseButtonPressedEvent event(button);
					data.callback(event);
					break;
				}
				case GLFW_RELEASE:  // Mouse button release event
				{
					MouseButtonReleasedEvent event(button);
					data.callback(event);
					break;
				}
				default:
					break;
				}
			});

		// Set callback for mouse scrolling events
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
			{
				// Retrieve window data and trigger a mouse scroll event
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseScrolledEvent event(xoffset, yoffset);
				data.callback(event);
			});

		// Set callback for mouse cursor position events
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
			{
				// Retrieve window data and trigger a mouse movement event
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseMovedEvent event((float)xpos, (float)ypos);
				data.callback(event);
			});

		// Return true to indicate successful initialization
		return true;
	}

	// Constructor: Initialize the window with given properties
	WinWindow::WinWindow(const WindowProperties& WinProp)
	{
		Init(WinProp);
	}

	// Check if the window should close
	bool WinWindow::ShouldClose() const
	{
		return true;  // Always return true (this could be adjusted for actual close logic)
	}

	// Poll window events (e.g., keyboard, mouse) and swap buffers
	void  WinWindow::PollEvents()
	{
		glfwPollEvents();  // Process all pending events
		SwapBuffers();  // Swap the front and back buffers for rendering
	}

	// Swap the front and back buffers
	void  WinWindow::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);  // Swap the current OpenGL buffers
	}

	// Clean up and shut down the window (destroy GLFW window)
	void WinWindow::ShutDown()
	{
		glfwDestroyWindow(m_Window);  // Destroy the GLFW window and clean up resources
	}

	// Factory method to create a new window instance
	Window* Window::Create(const WindowProperties& WinProp)
	{
		return new WinWindow(WinProp);  // Create and return a new WinWindow object
	}
}
