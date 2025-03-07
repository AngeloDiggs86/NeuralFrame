#pragma once

namespace NeuralEngine
{
	class GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffer() = 0;

	private:

	};
}