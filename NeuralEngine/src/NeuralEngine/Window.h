#pragma once
#include "Event/Event.h"
namespace NeuralEngine
{
	struct WindowProperties
	{
		std::string title;
		unsigned int width, height;

		WindowProperties(const std::string& _title = "Neural Engine", unsigned int _width = 1280, unsigned int _height = 720)
			:title(_title), width(_width), height(_height) {
		}
	};

	class Window {
	public:
		virtual ~Window() = default;
		virtual bool Init(const WindowProperties& WinProp) = 0;

		virtual bool ShouldClose() const = 0;

		virtual void PollEvents() = 0;

		virtual void SwapBuffers() = 0;

		virtual unsigned int GetWidth() const = 0;

		virtual unsigned int GetHeight() const = 0;

		virtual void ShutDown() = 0;

		using EventCallBackFn = std::function<void(Event&)>;

		virtual void SetEventCallBack(const EventCallBackFn& callback) = 0;

		static Window* Create(const WindowProperties& WinProp = WindowProperties());
	};
}
