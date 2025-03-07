#include "Enpch.h"
#include "OpenGLContext.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace NeuralEngine
{
	NeuralEngine::OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{
	}

	void NeuralEngine::OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);  // Set the current context for OpenGL rendering
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	}

	void NeuralEngine::OpenGLContext::SwapBuffer()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}