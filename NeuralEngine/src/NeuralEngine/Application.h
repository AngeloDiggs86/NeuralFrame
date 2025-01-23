#pragma once
#include "NeuralEngineCore.h"

namespace NeuralEngine
{
	class NEURAL_ENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	//To be defined in CLIENT
	Application* CreateApplication();
}


