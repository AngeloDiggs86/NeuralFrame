#pragma once 
#include "Event.h"  // Include base event class for event handling
/*
All ToString functions are for debug only and will be removed for release build.
*/
namespace NeuralEngine
{
    // Base class for keyboard-related events, derived from the Event class
    class KeyEvent : public Event
    {
    public:
        // Getter for the key code associated with the event
        int GetKeyCode() const { return m_keyCode; }

        // Macro to categorize the event as both a keyboard and input event
        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

    protected:
        // Constructor to initialize the keycode for the event
        KeyEvent(const int keycode)
            : m_keyCode(keycode) {
        }

        int m_keyCode;  // The key code for the key event (e.g., key press or release)
    };

    // KeyPressedEvent class, derived from KeyEvent, represents the event when a key is pressed
    class NEURAL_ENGINE_API KeyPressedEvent : public KeyEvent
    {
    public:
        // Constructor initializing keycode and whether the key press is a repeat
        KeyPressedEvent(const int keycode, bool isRepeat = false)
            : KeyEvent(keycode), m_IsRepeat(isRepeat) {
        }

        // Getter for checking if the key press is a repeat
        bool IsRepeat() const { return m_IsRepeat; }

        // Convert the event to a string representation
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_keyCode << " (repeat = " << m_IsRepeat << ")";  // Format output
            return ss.str();
        }

        // Macro to define the event type as KeyPressed
        EVENT_CLASS_TYPE(KeyPressed)
    private:
        bool m_IsRepeat;  // Flag to indicate if the key press is a repeat
    };

    // KeyReleasedEvent class, derived from KeyEvent, represents the event when a key is released
    class NEURAL_ENGINE_API KeyReleasedEvent : public KeyEvent
    {
    public:
        // Constructor initializing keycode for key release event
        KeyReleasedEvent(const int keycode)
            : KeyEvent(keycode) {
        }

        // Convert the event to a string representation
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_keyCode;  // Format output
            return ss.str();
        }

        // Macro to define the event type as KeyReleased
        EVENT_CLASS_TYPE(KeyReleased)
    };
}
