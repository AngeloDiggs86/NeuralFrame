#pragma once  // Ensure the file is included only once during compilation

#ifdef NE_PLATFORM_WINDOWS  // Conditional compilation for Windows platform

// Extern declaration of the CreateApplication function, which is defined in the client code
extern NeuralEngine::Application* NeuralEngine::CreateApplication();

// The main entry point of the application
int main(int argc, char** argv)
{
    // Initialize the logging system for the NeuralEngine
    NeuralEngine::Log::Init();

    // Create the application instance using the platform-specific method
    auto app = NeuralEngine::CreateApplication();

    // Run the application. This enters the main application loop
    app->Run();

    // Once the application loop finishes, clean up by deleting the app instance
    delete app;
}
#endif  // End of Windows-specific code block
