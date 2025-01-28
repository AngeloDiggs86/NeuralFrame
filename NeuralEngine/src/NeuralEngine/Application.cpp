#include "Event/ApplicationEvent.h"         
#include "Application.h"
#include "NeuralEngine/Log.h" 


namespace NeuralEngine
{
	Application::Application()
	{

	}
	
	Application::~Application()
	{

	}

	void Application::Run()
	{ 
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			EN_CORE_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			EN_CORE_TRACE(e);
		}
	
		while (1);
	}
}