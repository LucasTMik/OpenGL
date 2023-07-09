#pragma once
#include "Test.h"
#include <memory>

#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <Texture.h>

namespace Test {
	class TestBatchRendering : public Test
	{
	public:
		TestBatchRendering();
		~TestBatchRendering();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		std::unique_ptr<Shader> m_Shader = nullptr;
		std::unique_ptr<VertexBuffer> m_VB;
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		unsigned int m_IB;

		std::unique_ptr<Texture> m_Texture1;
		std::unique_ptr<Texture> m_Texture2;
	};
}