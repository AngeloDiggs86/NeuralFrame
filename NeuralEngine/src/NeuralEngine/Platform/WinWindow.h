#pragma once
#include "NeuralEngine/Window.h"
//Includes for Event System
#include "NeuralEngine/Event/ApplicationEvent.h"
#include "NeuralEngine/Event/KeyEvent.h"
#include "NeuralEngine/Event/MouseEvent.h"

#include "GLFW/glfw3.h"

namespace NeuralEngine
{
	class WinWindow : public Window
	{
	public:
		WinWindow(const WindowProperties& WinProp);
	
		virtual ~WinWindow();
		bool Init(const WindowProperties& WinProp) override;

		bool ShouldClose() const override;

		void PollEvents() override;
		 
		void SwapBuffers() override;

		void ShutDown() override;

		unsigned int GetWidth() const override {
			return m_data.width;
		}

		unsigned int GetHeight() const override {
			return m_data.height;
		}

		void SetEventCallBack(const EventCallBackFn& callback) override
		{
			m_data.callback = callback;
		}

	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string title  = "";
			unsigned int width = 0 , height = 0;
			EventCallBackFn callback = EventCallBackFn();
		};

		WindowData m_data;
	};
}
