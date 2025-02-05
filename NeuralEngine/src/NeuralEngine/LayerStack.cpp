#include "Enpch.h"  // Include the precompiled header for the engine
#include "LayerStack.h"  // Include the LayerStack class header

namespace NeuralEngine
{
	// Constructor for the LayerStack class, initializes the stack
	LayerStack::LayerStack() {}

	// Destructor for the LayerStack class, deletes all the layers in the stack
	LayerStack::~LayerStack()
	{
		// Iterate through each layer and delete it to prevent memory leaks
		for (Layer* layer : m_Layers)
			delete layer;
	}

	// Push a layer onto the stack at the position determined by m_LayerInsertIndex
	void LayerStack::PushLayer(Layer* layer)
	{
		// Insert the layer at the current index position
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		// Increment the insert index after adding the layer
		m_LayerInsertIndex++;
	}

	// Push an overlay layer onto the stack (overlays are added at the end of the stack)
	void LayerStack::PushOverlay(Layer* overlay)
	{
		// Simply add the overlay at the end of the vector
		m_Layers.emplace_back(overlay);
	}

	// Pop a specific layer from the stack
	void LayerStack::PopLayer(Layer* layer)
	{
		// Find the layer within the active layers (up to m_LayerInsertIndex)
		auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, layer);
		// If the layer is found in the active stack
		if (it != m_Layers.begin() + m_LayerInsertIndex)
		{
			// Remove the layer from the stack and decrement the insert index
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	// Pop a specific overlay from the stack
	void LayerStack::PopOverlay(Layer* overlay)
	{
		// Find the overlay in the range after m_LayerInsertIndex (the overlay section of the stack)
		auto it = std::find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), overlay);
		// If the overlay is found in the stack
		if (it != m_Layers.end())
		{
			// Remove the overlay from the stack
			m_Layers.erase(it);
		}
	}
}
