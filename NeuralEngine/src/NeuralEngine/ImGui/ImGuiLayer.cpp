/*
Copy and paste events need to be implemented
*/


#include "Enpch.h"
#include "ImGuiLayer.h"


#include "imgui.h"

#include "glad/glad.h"//TEMPORARY
#include "NeuralEngine/Platform/OpenGL/imGuiOpenGLRenderer.h" //TEMPORARY
#include "GLFW/glfw3.h" //TEMPORARY

#include "NeuralEngine/Application.h"

namespace NeuralEngine
{
	ImGuiLayer::ImGuiLayer()
		:Layer("ImGuiLayer")
	{

	}

	ImGuiLayer::~ImGuiLayer()
	{

	}

	void ImGuiLayer::OnAttach()
	{
        if (!glfwGetCurrentContext())
        {
            std::cerr << " No active OpenGL context!" << std::endl;
        }

		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();

		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        //TEMPORARY
        io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
        io.KeyMap[ImGuiKey_LeftArrow] =     GLFW_KEY_LEFT;
        io.KeyMap[ImGuiKey_RightArrow] =    GLFW_KEY_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow] =       GLFW_KEY_UP;
        io.KeyMap[ImGuiKey_DownArrow] =     GLFW_KEY_DOWN;
        io.KeyMap[ImGuiKey_PageUp] =        GLFW_KEY_PAGE_UP;
        io.KeyMap[ImGuiKey_PageDown] =      GLFW_KEY_PAGE_DOWN;
        io.KeyMap[ImGuiKey_Home] =          GLFW_KEY_HOME;
        io.KeyMap[ImGuiKey_End] =           GLFW_KEY_END;
        io.KeyMap[ImGuiKey_Insert] =        GLFW_KEY_INSERT;
        io.KeyMap[ImGuiKey_Delete] =        GLFW_KEY_DELETE;
        io.KeyMap[ImGuiKey_Backspace] =     GLFW_KEY_BACKSPACE;
        io.KeyMap[ImGuiKey_Space] =         GLFW_KEY_SPACE;
        io.KeyMap[ImGuiKey_Enter] =         GLFW_KEY_ENTER;
        io.KeyMap[ImGuiKey_0] =             GLFW_KEY_0;
        io.KeyMap[ImGuiKey_1] =             GLFW_KEY_1;
        io.KeyMap[ImGuiKey_2] =             GLFW_KEY_2;
        io.KeyMap[ImGuiKey_3] =             GLFW_KEY_3;
        io.KeyMap[ImGuiKey_4] =             GLFW_KEY_4;
        io.KeyMap[ImGuiKey_5] =             GLFW_KEY_5;
        io.KeyMap[ImGuiKey_6] =             GLFW_KEY_6;
        io.KeyMap[ImGuiKey_7] =             GLFW_KEY_7;
        io.KeyMap[ImGuiKey_8] =             GLFW_KEY_8;
        io.KeyMap[ImGuiKey_9] =             GLFW_KEY_9;
        io.KeyMap[ImGuiKey_A] =             GLFW_KEY_A;
        io.KeyMap[ImGuiKey_B] =             GLFW_KEY_B;
        io.KeyMap[ImGuiKey_C] =             GLFW_KEY_C;
        io.KeyMap[ImGuiKey_D] =             GLFW_KEY_D;
        io.KeyMap[ImGuiKey_E] =             GLFW_KEY_E;
        io.KeyMap[ImGuiKey_F] =             GLFW_KEY_F;
        io.KeyMap[ImGuiKey_G] =             GLFW_KEY_G;
        io.KeyMap[ImGuiKey_H] =             GLFW_KEY_H;
        io.KeyMap[ImGuiKey_I] =             GLFW_KEY_I;
        io.KeyMap[ImGuiKey_J] =             GLFW_KEY_J;
        io.KeyMap[ImGuiKey_K] =             GLFW_KEY_K;
        io.KeyMap[ImGuiKey_L] =             GLFW_KEY_L;
        io.KeyMap[ImGuiKey_M] =             GLFW_KEY_M;
        io.KeyMap[ImGuiKey_N] =             GLFW_KEY_N;
        io.KeyMap[ImGuiKey_O] =             GLFW_KEY_O;
        io.KeyMap[ImGuiKey_P] =             GLFW_KEY_P;
        io.KeyMap[ImGuiKey_Q] =             GLFW_KEY_Q;
        io.KeyMap[ImGuiKey_R] =             GLFW_KEY_R;
        io.KeyMap[ImGuiKey_S] =             GLFW_KEY_S;
        io.KeyMap[ImGuiKey_T] =             GLFW_KEY_T;
        io.KeyMap[ImGuiKey_U] =             GLFW_KEY_U;
        io.KeyMap[ImGuiKey_V] =             GLFW_KEY_V;
        io.KeyMap[ImGuiKey_W] =             GLFW_KEY_W;
        io.KeyMap[ImGuiKey_X] =             GLFW_KEY_X;
        io.KeyMap[ImGuiKey_Y] =             GLFW_KEY_Y;
        io.KeyMap[ImGuiKey_Z] =             GLFW_KEY_Z;
      

        s_Initialized = ImGui_ImplOpenGL3_Init("#version 460");
	}

	void ImGuiLayer::OnDetach()
	{

	}

	void ImGuiLayer::OnEvent(Event& e)
	{
        EventDispatcher dispatcher(e);

        dispatcher.Dispatch<MouseButtonPressedEvent>(EN_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
        dispatcher.Dispatch<MouseButtonReleasedEvent>(EN_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
        dispatcher.Dispatch<MouseMovedEvent>(EN_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
        dispatcher.Dispatch<MouseScrolledEvent>(EN_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
        dispatcher.Dispatch<KeyPressedEvent>(EN_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
        dispatcher.Dispatch<KeyReleasedEvent>(EN_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
        dispatcher.Dispatch<WindowResizeEvent>(EN_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
        dispatcher.Dispatch<KeyTypedEvent>(EN_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
	}

    bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
    {
        std::cout << "Mouse button pressed: " << e.GetMouseButton() << std::endl;
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[e.GetMouseButton()] = true;
        return false;
    }

    bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e) // Window crashes when mouse button is released 
    {
        ImGuiIO& io = ImGui::GetIO();
        int button = e.GetMouseButton();
        std::cout << "Mouse button " << button << " released." << std::endl;

        // Debug the state of MouseDown before modification
        std::cout << "Before: ";
        for (int i = 0; i < 5; ++i)
        {
            std::cout << io.MouseDown[i] << " ";
        }
        std::cout << std::endl;

        if (button >= 0 && button < 5)
        {
            io.MouseDown[button] = false;  // Set to false
        }

        // Debug the state of MouseDown after modification
        std::cout << "After: ";
        for (int i = 0; i < 5; ++i)
        {
            std::cout << io.MouseDown[i] << " ";
        }
        std::cout << std::endl;
        //io.MouseDown[e.GetMouseButton()] = false;
        return false;
    } 

    bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos = ImVec2(e.GetX(), e.GetY());
        return false;
    }

    bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseWheel += e.GetYOffset();
        io.MouseWheelH += e.GetYOffset();
        return false;
    }

    bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[e.GetKeyCode()] = true;
        io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
        io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
        io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
        io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
        return false;
    }

    bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[e.GetKeyCode()] = false;
        return false;
    }

    bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        int keyCode = e.GetKeyCode();

        io.AddInputCharacter(keyCode);
        return false;
    }

    bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(e.GetWidth(), e.GetHieght());
        io.DisplayFramebufferScale = ImVec2(1.0f,1.0f);
        glViewport(0, 0, e.GetWidth(), e.GetHieght());
        return false;
    }

	void ImGuiLayer::OnUpdate()
	{
        ImGuiIO& io = ImGui::GetIO();

        Application& app = Application::Get();

        io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

        float time = (float)glfwGetTime();

        io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
        m_Time = time;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        static bool show = false;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}