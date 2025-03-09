#include "Enpch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "NeuralEngine/Platform/OpenGL/OpenGLVertexArray.h"

namespace NeuralEngine
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:		NE_CORE_ERROR("RendererAPI::None is not currently supported!"); return nullptr;
		case RendererAPI::OpenGL:   return new OpenGLVertexArray();
		}
		NE_CORE_ERROR("Unknown RendererAPI!");
		return nullptr;
	}
}