#pragma once
#include "Camera.h"

namespace NeuralEngine
{
	class OrthoCamera : public Camera
	{
	public:
		OrthoCamera(float left, float right, float bottom, float top, float nearPlane = -1.0f, float farPlane = 1.0f);

		inline virtual void SetPosition(const glm::vec3& postion) override { m_Position = postion; RecalculateViewMatrix(); };
		inline virtual const glm::vec3& GetPosition() const override { return m_Position; };
		inline virtual void SetRotation(const float& rotation) override { m_Rotation = rotation; RecalculateViewMatrix(); };
		inline virtual float GetRotation() const { return m_Rotation; }

		virtual glm::mat4 const& GetProjectionMat() const override;
		virtual glm::mat4 const& GetViewMat() const override;
		virtual glm::mat4 const& GetVPMat() const override;

	private:
		virtual void RecalculateViewMatrix() override;
	private:
		glm::mat4 m_ProjectionMat = glm::mat4(1.0f);
		glm::mat4 m_ViewMat = glm::mat4(1.0f);
		glm::mat4 m_VPMat = glm::mat4(1.0f);
		glm::vec3 m_Position;
		float m_Rotation = 0.0f;
	};
}