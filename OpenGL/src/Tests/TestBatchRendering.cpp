#include "TestBatchRendering.h"
#include "Renderer.h"
#include <glm/gtc/matrix_transform.hpp>

#include "VertexBufferLayout.h"

namespace Test {
	TestBatchRendering::TestBatchRendering()
	{
		m_Shader = std::unique_ptr<Shader>(Shader::FromGLSLTextFiles(
			"res/shaders/shader.glsl.vert", "res/shaders/shader.glsl.frag"
		));
		//m_Shader = std::unique_ptr<Shader>(new Shader("res/shaders/Basic.shader"));

		float buffer[] = {
			200.0f, 100.0f, 0.0f, 1.0f, 1.0f, 1.0f,
			200.0f, 200.0f, 0.0f,  1.0f, 0.0f, 0.0f,
			300.0f, 200.0f, 0.0f,   0.0f, 0.0f, 1.0f,
			300.0f, 100.0f, 0.0f,  0.0f, 1.0f, 0.0f,

			100.0f, 100.0f, 0.0f, 0.0f, 6.0f, 0.0f,
			100.0f, 200.0f, 0.0f,  0.0f, 6.0f, 0.0f,
			200.0f, 200.0f, 0.0f,   0.0f, 6.0f, 0.0f,
			200.0f, 100.0f, 0.0f,  0.0f, 6.0f, 0.0f
		};

		uint32_t indices[] = {
			0, 1, 2, 2, 3, 0,
			4, 5, 6, 6, 7, 4
		};


		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 12);
		m_VB = std::make_unique<VertexBuffer>(buffer, sizeof(buffer));
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		
		m_VAO = std::make_unique<VertexArray>();
		m_VAO->AddBuffer(*m_VB, layout);
	}

	TestBatchRendering::~TestBatchRendering()
	{
		
	}

	void TestBatchRendering::OnUpdate(float deltaTime)
	{
		
	}

	void TestBatchRendering::OnRender()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		m_Shader->Bind();

		glm::mat4 mvp = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
		m_Shader->SetUniformMat4f("u_MVP", mvp);

		m_VAO->Bind();
		m_IndexBuffer->Bind();
		glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void TestBatchRendering::OnImGuiRender()
	{
	}


}