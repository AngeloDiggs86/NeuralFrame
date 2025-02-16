#pragma once
#include "NeuralEngine/Input.h"
namespace NeuralEngine
{
	class WindowsInput : public Input
	{
	protected :
		virtual bool IsKeyPressedImpl(int keyCode) override;
		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float IsMouseXPosImpl() override;
		virtual float IsMouseYPosImpl() override;
	};
}