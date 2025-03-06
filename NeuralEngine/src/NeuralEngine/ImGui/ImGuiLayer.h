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
		virtual void OnDetach() override;
		virtual void OnAttach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
		bool s_Initialized = true;
	};
}