#pragma once

#ifdef NE_PLATFORM_WINDOWS

extern NeuralEngine::Application* NeuralEngine::CreateApplication();

int main(int argc, char** argv)
{
	auto app = NeuralEngine::CreateApplication();
	app->Run();
	delete app;
}
#endif 