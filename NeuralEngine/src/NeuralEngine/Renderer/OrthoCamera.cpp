#include "Enpch.h"
#include "OrthoCamera.h"
#include "glm/gtc/matrix_transform.hpp"

namespace NeuralEngine
{
	OrthoCamera::OrthoCamera(float left, float right, float bottom, float top, float nearPlane, float farPlane)
		:m_ProjectionMat(glm::ortho(left, right, bottom, top, nearPlane, farPlane)), m_ViewMat(1.0), m_Position(0.0f,0.0f,0.0f) {

		m_VPMat = m_ProjectionMat * m_ViewMat;
	}
	glm::mat4 const& OrthoCamera::GetProjectionMat() const 
	{
		return m_ProjectionMat;
	}
	glm::mat4 const& OrthoCamera::GetViewMat() const 
	{
		return m_ViewMat;
	}
	glm::mat4 const& OrthoCamera::GetVPMat() const
	{
		return m_VPMat;
	}

	void OrthoCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f));

		m_ViewMat = glm::inverse(transform);
		m_VPMat = m_ProjectionMat * m_ViewMat;
	}
}