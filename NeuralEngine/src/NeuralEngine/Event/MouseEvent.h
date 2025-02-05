#include "Enpch.h"  // Include precompiled header for faster compilation
#include "Event.h"  // Include base event class for event handling
#include <sstream>  // Include stringstream for event string conversion
/*
All ToString functions are for debug only and will be removed for release build. 
*/
namespace NeuralEngine {

	// Represents an event for mouse movement, derived from the Event class
	class NEURAL_ENGINE_API MouseMovedEvent : public Event
	{
	public:
		// Constructor to initialize mouse x and y positions
		MouseMovedEvent(const float x, const float y)
			: m_MouseX(x), m_MouseY(y) {
		}

		// Getter for the x-coordinate of the mouse position
		float GetX() const { return m_MouseX; }

		// Getter for the y-coordinate of the mouse position
		float GetY() const { return m_MouseY; }

		// Convert the event to a string representation
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;  // Format the mouse position
			return ss.str();
		}

		// Macro to define the event type as MouseMoved
		EVENT_CLASS_TYPE(MouseMoved)

		// Macro to categorize the event as a mouse and input event
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_MouseX, m_MouseY;  // Mouse position coordinates
	};

	// Represents an event for mouse scrolling, derived from the Event class
	class NEURAL_ENGINE_API MouseScrolledEvent : public Event
	{
	public:
		// Constructor to initialize scroll offsets for x and y axes
		MouseScrolledEvent(const float xOffset, const float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {
		}

		// Getter for the x offset of the scroll event
		float GetXOffset() const { return m_XOffset; }

		// Getter for the y offset of the scroll event
		float GetYOffset() const { return m_YOffset; }

		// Convert the event to a string representation 
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();  // Format the scroll offsets
			return ss.str();
		}

		// Macro to define the event type as MouseScrolled
		EVENT_CLASS_TYPE(MouseScrolled)

		// Macro to categorize the event as a mouse and input event
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_XOffset, m_YOffset;  // Scroll offsets for x and y axes
	};

	// Base class for mouse button events, derived from the Event class
	class NEURAL_ENGINE_API MouseButtonEvent : public Event
	{
	public:
		// Getter for the mouse button involved in the event
		inline int GetMouseButton() const { return m_Button; }

		// Macro to categorize the event as a mouse, input, and mouse button event
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton)
	protected:
		// Constructor to initialize the mouse button for the event
		MouseButtonEvent(const int button)
			: m_Button(button) {
		}

		int m_Button;  // The mouse button involved in the event (e.g., left or right button)
	};

	// Represents an event for mouse button press, derived from MouseButtonEvent
	class NEURAL_ENGINE_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		// Constructor to initialize the mouse button for the press event
		MouseButtonPressedEvent(const int button)
			: MouseButtonEvent(button) {
		}

		// Convert the event to a string representation 
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;  // Format the button press event
			return ss.str();
		}

		// Macro to define the event type as MouseButtonPressed
		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	// Represents an event for mouse button release, derived from MouseButtonEvent
	class NEURAL_ENGINE_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		// Constructor to initialize the mouse button for the release event
		MouseButtonReleasedEvent(const int button)
			: MouseButtonEvent(button) {
		}

		// Convert the event to a string representation
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;  // Format the button release event
			return ss.str();
		}

		// Macro to define the event type as MouseButtonReleased
		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

}
