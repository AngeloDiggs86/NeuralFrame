#pragma once

#include "NeuralEngine/Layer.h"
#include "NeuralEngine//Event/ApplicationEvent.h"
#include "NeuralEngine/Event/MouseEvent.h"
#include "NeuralEngine/Event/KeyEvent.h"


namespace NeuralEngine
{
	class NEURAL_ENGINE_API ImGuiLayer: public Layer
	{
	public:

		ImGuiLayer();
		~ImGuiLayer();
		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& e) override;
	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);
	private:
		float m_Time = 0.0f;
		bool s_Initialized = true;
	};
}