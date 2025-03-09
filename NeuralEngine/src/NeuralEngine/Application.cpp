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

	Application::Application()
	{
		s_Instance = this;
		// Create the window and store it in m_Window
		m_Window = std::unique_ptr<Window>(Window::Create());

		// Set the event callback to the OnEvent method of Application
		m_Window->SetEventCallBack(BIND_EVENT(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		m_VertexArray.reset(VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f , -0.5f ,  0.0f, 1.0f, 0.0f, 1.0f, 1.0,
			 0.5f , -0.5f ,  0.0f, 1.0f, 1.0f, 0.0f, 1.0,
			 0.0f ,  0.5f ,  0.0f, 0.0f, 0.0f, 1.0f, 1.0
		};

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices ,sizeof(vertices)));

		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };

		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, 3));
		m_VertexArray->SetIndexBuffer(indexBuffer);





		m_SquareVA.reset(VertexArray::Create());


		float squareVertices[3 * 4] = {
			-0.75f , -0.75f ,  0.0f, 
			 0.75f , -0.75f ,  0.0f, 
			 0.75f ,  0.75f ,  0.0f,
			-0.75f ,  0.75f ,  0.0f
		};

		std::shared_ptr<VertexBuffer> squareVB;
		 squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		BufferLayout squareLayout = {
			{ShaderDataType::Float3, "a_Position"}
		};

		squareVB->SetLayout(squareLayout);
		m_SquareVA->AddVertexBuffer(squareVB);

		unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, 6));
		m_SquareVA->SetIndexBuffer(squareIB);

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
				color = vec4(v_Position, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));

		std::string BlueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;
		

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string BlueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new Shader(BlueShaderVertexSrc, BlueShaderFragmentSrc));
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

			m_BlueShader->Bind();
			m_SquareVA->Bind();
			glDrawElements(GL_TRIANGLES, m_SquareVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			m_Shader->Bind();
			m_VertexArray->Bind();

			glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

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