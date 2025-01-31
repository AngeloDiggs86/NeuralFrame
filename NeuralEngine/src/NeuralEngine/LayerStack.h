#pragma once
#include "Enpch.h"
#include "Layer.h"
namespace NeuralEngine {

	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();
		virtual void PushLayer(Layer* layer);
		virtual void PushOverlay(Layer* overlay);
		virtual void PopLayer(Layer* layer);
		virtual void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex = 0;
	};
}