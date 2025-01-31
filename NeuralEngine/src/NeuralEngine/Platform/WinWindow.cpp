#include "Enpch.h"
#include "WinWindow.h"



namespace NeuralEngine
{
	static bool s_GLFWInitialized = false;

	WinWindow::~WinWindow() {
		ShutDown();
	}

	bool WinWindow::Init(const WindowProperties& WinProp)
	{
		m_data.title = WinProp.title;
		m_data.width = WinProp.width;
		m_data.height = WinProp.height;

		EN_CORE_INFO("Window Details: {0} , {1} , {2}", m_data.title , m_data.width , m_data.height);

		if (!s_GLFWInitialized)
		{
			glfwInit();
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)m_data.width, (int)m_data.height, m_data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_data);
		glfwSwapInterval(1);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.width = width;
			data.height = height;

			WindowResizeEvent event(width, height);

			data.callback(event);
		});
		
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.callback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, false);
					data.callback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.callback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, true);
					data.callback(event);
					break;
				}
				default:
					break;
			}
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case  GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.callback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.callback(event);
					break;
				}
				default:
					break;
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event(xoffset, yoffset);
			data.callback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event((float)xpos, (float)ypos);
			data.callback(event);
		});
		
		return true;
	}

	WinWindow::WinWindow(const WindowProperties& WinProp)
	{
		Init(WinProp);
	}

	bool WinWindow::ShouldClose() const
	{
		return true;
	}

	void  WinWindow::PollEvents()
	{
		glfwPollEvents();
		SwapBuffers();
	}

	void  WinWindow::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}

	void WinWindow::ShutDown()
	{
		glfwDestroyWindow(m_Window);
	}

	Window* Window::Create(const WindowProperties& WinProp)
	{
		return new WinWindow(WinProp);
	}
}
