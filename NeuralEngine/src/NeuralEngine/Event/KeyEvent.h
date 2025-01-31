#pragma once
#include "Event.h"


namespace NeuralEngine
{
    class KeyEvent : public Event
    {
    public: 
        int GetKeyCode() const { return m_keyCode; }

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

    protected:
        KeyEvent(const int keycode)
            : m_keyCode(keycode) {
        }
       
        int m_keyCode;
    };

    class NEURAL_ENGINE_API KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(const int keycode, bool isRepeat = false)
            : KeyEvent(keycode), m_IsRepeat(isRepeat) {
        }

        bool IsRepeat() const { return m_IsRepeat; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_keyCode << " (repeat = " << m_IsRepeat << ")";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)
    private:
        bool m_IsRepeat;
    };

    class NEURAL_ENGINE_API KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(const int keycode)
            : KeyEvent(keycode) {
        }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_keyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };
}