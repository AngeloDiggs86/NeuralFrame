#pragma once 
#include "Enpch.h"  // Include precompiled header for faster compilation
#include "NeuralEngine/NeuralEngineCore.h"  // Include core engine functionalities

namespace NeuralEngine
{
	// Enum to define different event types
	enum class EventType
	{
		None = 0,  // No event
		WindowCloseEvent, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,  // Window related events
		AppTick, AppUpdate, AppRender,  // Application lifecycle events
		KeyPressed, KeyReleased, KeyTyped,  // Keyboard input events
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled  // Mouse input events
	};

	// Enum to categorize different types of events
	enum EventCategory
	{
		None = 0,  // No category
		EventCategoryApplication = BIT(0),  // Application events
		EventCategoryInput = BIT(1),  // Input events (keyboard, mouse)
		EventCategoryKeyboard = BIT(2),  // Keyboard events
		EventCategoryMouse = BIT(3),  // Mouse events
		EventCategoryMouseButton = BIT(4)   // Mouse button events
	};

	// Macro to define the event type for derived event classes
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

	// Macro to associate event with its category
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

// Base Event class that all events derive from
	class NEURAL_ENGINE_API Event
	{
	public:
		virtual ~Event() = default;  // Virtual destructor to allow proper cleanup of derived classes

		bool Handled = false;  // Flag to indicate if the event was handled

		// Pure virtual functions to be implemented by derived event types
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }  // Default string conversion

		// Check if the event belongs to a specific category
		bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;  // Uses bitwise AND to check category
		}
	};

	// EventDispatcher class to handle dispatching events
	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)  // Constructor initializes with the event to be dispatched
			: m_Event(event)
		{
		}

		// Dispatches the event to the appropriate handler function
		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			// Check if the event type matches the specified type
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				// Call the handler function with the event and mark it as handled
				m_Event.Handled |= func(static_cast<T&>(m_Event));
				return true;
			}
			return false;  // If event type does not match, return false
		}

	private:
		Event& m_Event;  // Reference to the event to be dispatched
	};

	// Overload of the output stream operator for easy event printing
	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();  // Use ToString to convert event to a string
	}
}
