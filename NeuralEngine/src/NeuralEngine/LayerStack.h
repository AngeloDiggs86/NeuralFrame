#pragma once
#include "Enpch.h"  // Include the precompiled header for the engine
#include "Layer.h"   // Include the Layer class header for working with layers

namespace NeuralEngine {

	// The LayerStack class manages a collection of layers and overlays,
	// providing functionality to push and pop them while maintaining order.
	class LayerStack
	{
	public:
		// Constructor for the LayerStack class, initializes an empty stack
		LayerStack();

		// Destructor for the LayerStack class, ensures all layers are cleaned up
		~LayerStack();

		// Push a regular layer onto the stack at the current insertion index
		virtual void PushLayer(Layer* layer);

		// Push an overlay layer onto the stack at the end of the vector
		virtual void PushOverlay(Layer* overlay);

		// Pop a specific layer from the stack if it exists in the active layer range
		virtual void PopLayer(Layer* layer);

		// Pop a specific overlay from the stack if it exists in the overlay section
		virtual void PopOverlay(Layer* overlay);

		// Iterator for the beginning of the stack, useful for range-based for loops
		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }

		// Iterator for the end of the stack, useful for range-based for loops
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:
		// Internal storage for layers and overlays, with active layers first
		std::vector<Layer*> m_Layers;

		// Index that indicates the position where layers should be inserted
		unsigned int m_LayerInsertIndex = 0;
	};
}
