#pragma once
#include "NeuralEngine/NeuralEngineCore.h"

namespace NeuralEngine
{
	class NEURAL_ENGINE_API Input
	{
	public:
		inline static bool IsKeyPressed(int keyCode) { return s_Instance->IsKeyPressedImpl(keyCode); }
		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float,float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		inline static float IsMouseXPos() { return s_Instance->IsMouseXPosImpl(); }
		inline static float IsMouseYPos() { return s_Instance->IsMouseYPosImpl(); }
	protected:
		virtual bool IsKeyPressedImpl(int keyCode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float IsMouseXPosImpl() = 0;
		virtual float IsMouseYPosImpl() = 0;
	private:
		static Input* s_Instance;
	};
}