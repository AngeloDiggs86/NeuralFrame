#include "Enpch.h"
#include "Renderer.h"

namespace NeuralEngine
{
	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(Camera& camera)
	{
		s_SceneData->VeiwProjMatrix = camera.GetVPMat();
	}
	void Renderer::EndScene()
	{
	}
	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader)
	{
		shader->Bind();
		shader->UploadUniformMat4(s_SceneData->VeiwProjMatrix, "u_ViewProj");
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}