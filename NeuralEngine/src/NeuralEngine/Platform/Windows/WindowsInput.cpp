#include "Enpch.h"
#include "WindowsInput.h"

#include "NeuralEngine/Application.h"
#include "GLFW/glfw3.h"

namespace NeuralEngine
{
	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keyCode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keyCode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, button);
		return state == GLFW_PRESS;
	}
	float WindowsInput::IsMouseXPosImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return x;
	}
	float WindowsInput::IsMouseYPosImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return y;
	}
	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float)ypos, (float)ypos };
	}
}