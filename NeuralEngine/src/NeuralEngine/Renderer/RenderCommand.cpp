#include "Enpch.h"
#include "RenderCommand.h"
#include "NeuralEngine//Platform/OpenGL/OpenGLRendererAPI.h"

namespace NeuralEngine
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}