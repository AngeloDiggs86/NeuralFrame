#include "Enpch.h"  // Precompiled header for faster compilation
#include "Application.h"  // Include the header for the Application class
#include "NeuralEngine/Log.h"  // Include the logging system

//#include "Event/MouseEvent.h"  // Include event classes for mouse events

#include "glad/glad.h"
#include "Input.h"

namespace NeuralEngine
{
	Application* Application::s_Instance = nullptr;
	// The Application class is the main entry point and controller for the engine

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type) {
			case ShaderDataType::Float:		return GL_FLOAT;
			case ShaderDataType::Float2:	return GL_FLOAT;
			case ShaderDataType::Float3:	return GL_FLOAT;
			case ShaderDataType::Float4:	return GL_FLOAT;
			case ShaderDataType::Mat3:		return GL_FLOAT;
			case ShaderDataType::Mat4:		return GL_FLOAT;
			case ShaderDataType::Int:		return GL_INT;
			case ShaderDataType::Int2:		return GL_INT;
			case ShaderDataType::Int3:		return GL_INT;
			case ShaderDataType::Int4:		return GL_INT;
			case ShaderDataType::Bool:		return GL_BOOL;
		}
		NE_CORE_ERROR("Unknown Shader Type!");
		return 0;
	}

	Application::Application()
	{
		s_Instance = this;
		// Create the window and store it in m_Window
		m_Window = std::unique_ptr<Window>(Window::Create());

		// Set the event callback to the OnEvent method of Application
		m_Window->SetEventCallBack(BIND_EVENT(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		// Vertex Array
		// Vertex Buffer
		// Index Buffer

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		float vertices[3 * 7] = {
			-0.5f , -0.5f ,  0.0f, 1.0f, 0.0f, 1.0f, 1.0,
			 0.5f , -0.5f ,  0.0f, 1.0f, 1.0f, 0.0f, 1.0,
			 0.0f ,  0.5f ,  0.0f, 0.0f, 0.0f, 1.0f, 1.0
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices ,sizeof(vertices)));

		{
			BufferLayout layout = {
				{ShaderDataType::Float3, "a_Position"},
				{ShaderDataType::Float4, "a_Color" }
			};

			m_VertexBuffer->SetLayout(layout);
		}

		const auto& layout = m_VertexBuffer->GetLayout();
		uint32_t index = 0;
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(), 
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE, 
				layout.GetStride(), 
				(const void*)element.Offset);
			++index;
		}

		unsigned int indices[3] = { 0, 1 , 2 };

		m_IndexBuffer.reset(IndexBuffer::Create(indices, 3));

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
	}

	// Destructor for the Application class
	Application::~Application()
	{
		// Clean up resources here if necessary
	}

	// Handle events passed to the application
	void Application::OnEvent(Event& e)
	{
		// Create an event dispatcher to handle events
		EventDispatcher dispatcher(e);

		// Dispatch the WindowCloseEvent to the OnWindowClose method
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT(OnWindowClose));

		// Process the event through all layers in the layer stack
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);  // Pass the event to each layer
			if (e.Handled)  // If the event is handled, stop further propagation
				break;
		}
	}

	// Main loop for running the application
	void Application::Run()
	{
		// The application continues running while m_Running is true
		while (m_Running)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();

			glBindVertexArray(m_VertexArray);
		
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			m_Window->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->SwapBuffer();
		}
	}

	// Method to handle the WindowCloseEvent, sets m_Running to false to exit the application
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;  // Stop the application
		return m_Running;
	}

	// Push a layer onto the layer stack (layers are rendered in order)
	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	// Push an overlay layer onto the layer stack (overlays are rendered on top of layers)
	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}
}