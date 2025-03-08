#include "Enpch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "NeuralEngine/Platform/OpenGL/OpenGLBuffer.h"

namespace NeuralEngine
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:		NE_CORE_ERROR("RendererAPI::None is not currently supported!"); return nullptr;
		case RendererAPI::OpenGL:   return new OpenGLVertexBuffer(vertices, size);
		}
		NE_CORE_ERROR("Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:		NE_CORE_ERROR("RendererAPI::None is not currently supported!"); return nullptr;
		case RendererAPI::OpenGL:   return new OpenGLIndexBuffer(indices, count);
		}
		NE_CORE_ERROR("Unknown RendererAPI!");
		return nullptr;
	}
}

