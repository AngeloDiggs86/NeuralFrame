#pragma once
#include "NeuralEngine/Renderer/RenderCommand.h"
#include "OrthoCamera.h"
#include "Shader.h"

namespace NeuralEngine
{
	class Renderer
	{
	public:
		static void BeginScene(Camera& camera);
		static void EndScene();
		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader);
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	
	private:
		struct SceneData {
			glm::mat4 VeiwProjMatrix;
		};
		static SceneData* s_SceneData;
	};
}