#pragma once
#include "glm/glm.hpp"

namespace NeuralEngine
{
	class Camera
	{
	public:
		virtual const glm::vec3& GetPosition() const = 0;
		virtual void SetPosition(const glm::vec3& postion) = 0;
		virtual void SetRotation(const float& rotation) = 0;
		virtual float GetRotation() const = 0;

		virtual glm::mat4 const& GetProjectionMat() const = 0;
		virtual glm::mat4 const& GetViewMat() const = 0;
		virtual glm::mat4 const& GetVPMat() const = 0;

	private:
		virtual void RecalculateViewMatrix() = 0;
	};
}