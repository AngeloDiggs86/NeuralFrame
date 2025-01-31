#pragma once
#include "NeuralEngineCore.h"
#include "Event/Event.h"
namespace NeuralEngine
{
    class NEURAL_ENGINE_API Layer {
    public:
        Layer(std::string) {};
        virtual ~Layer() = default;
        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate() {}
        virtual void OnEvent(Event& e) {}

        inline const std::string GetName() { return m_DebugName; }

    private:
        std::string m_DebugName;
    };
}

