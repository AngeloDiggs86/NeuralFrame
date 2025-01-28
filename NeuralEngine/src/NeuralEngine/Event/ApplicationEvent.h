#pragma once

#include "Event.h"
#include <sstream>
namespace NeuralEngine
{
	class NEURAL_ENGINE_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int hieght, unsigned int width)
			: m_Hieght(hieght), m_Width(width) {
		}

		unsigned int GetHieght() { return m_Hieght; }
		unsigned int GetWidth() { return m_Width; }

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Hieght;
			return ss.str();
		}

	private:
		unsigned int m_Hieght, m_Width;
	};

	class NEURAL_ENGINE_API WindowClose : public Event
	{
		WindowClose() = default;

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}