#pragma once  // Ensure the file is included only once during compilation

#include "NeuralEngineCore.h"  // Include the core engine header
#include "Event/Event.h"  // Include the event system header

namespace NeuralEngine
{
    // The Layer class represents a layer in the application that can be updated, attached, and respond to events
    class NEURAL_ENGINE_API Layer {
    public:
        // Constructor for the Layer class that accepts a name for debugging purposes
        //Layer(std::string name) : m_DebugName(name) {};

        Layer(std::string name)
        {
            m_DebugName = name;
        }

        // Virtual destructor, allows proper cleanup of derived classes
        virtual ~Layer() = default;

        // Method to handle when the layer is attached to the application (called when the layer is added to the stack)
        virtual void OnAttach() {}

        // Method to handle when the layer is detached from the application (called when the layer is removed)
        virtual void OnDetach() {}

        // Method to handle updates for the layer (called every frame during the main loop)
        virtual void OnUpdate() {}

        // Method to handle events for the layer (used to process events specific to this layer)
        virtual void OnEvent(Event& e) {}

        // Inline method to get the name of the layer for debugging purposes
        inline const std::string GetName() { return m_DebugName; }

    private:
        std::string m_DebugName;  // Debug name of the layer, used to identify the layer during debugging
    };
}


