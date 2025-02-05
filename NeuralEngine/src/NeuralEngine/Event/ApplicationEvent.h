#pragma once
#include "Event.h"  // Include header file for the Event class
/*
All ToString functions are for debug only and will be removed for release build.
*/
namespace NeuralEngine
{
	// Represents an event for window resizing
	class NEURAL_ENGINE_API WindowResizeEvent : public Event
	{
	public:
		// Constructor initializing the event with height and width values
		WindowResizeEvent(unsigned int hieght, unsigned int width)
			: m_Hieght(hieght), m_Width(width) {
		}

		// Getter for the height of the window
		unsigned int GetHieght() { return m_Hieght; }

		// Getter for the width of the window
		unsigned int GetWidth() { return m_Width; }

		// Macro to associate the event with a type (WindowResize)
		EVENT_CLASS_TYPE(WindowResize)

			// Macro to categorize the event as an application-related event
			EVENT_CLASS_CATEGORY(EventCategoryApplication)

			// Overridden ToString function to convert event details to string
			std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Hieght; // Format event data into string
			return ss.str();
		}

	private:
		// Member variables for window height and width
		unsigned int m_Hieght, m_Width;
	};

	// Represents an event for window close
	class NEURAL_ENGINE_API WindowCloseEvent : public Event
	{
	public:
		// Default constructor for window close event
		WindowCloseEvent() = default;

		// Macro to associate the event with a type (WindowCloseEvent)
		EVENT_CLASS_TYPE(WindowCloseEvent)

			// Macro to categorize the event as an application-related event
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}
