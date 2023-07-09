#include "TestDefault.h"
#include "Renderer.h"
#include "imgui/imgui.h"
#include "TestClearColor.h"

#include <iostream>

namespace Test {
	TestDefault::TestDefault() : m_CurrentTest(nullptr)
	{
	
	}

	TestDefault::~TestDefault()
	{
		
	}

	void TestDefault::OnUpdate(float deltaTime)
	{
	}
	void TestDefault::OnRender()
	{
		if (m_CurrentTest == nullptr)
		{
			static float clearColor[3] = { 0.2f, 0.2f, 0.2f };
			GLCall(glClearColor(clearColor[0], clearColor[1], clearColor[2], 1.0f));
		}
		else
		{
			m_CurrentTest->OnRender();
		}
	}
	void TestDefault::OnImGuiRender()
	{
		ImGui::Begin("Tests");
		ImGui::Text("Existent tests");
		static bool isClearColor = false;
		if (ImGui::Checkbox("TestClearColor", &isClearColor))
		{
			m_CurrentTest = std::shared_ptr<TestClearColor>(new TestClearColor);
		}
		else if(!isClearColor)
		{
			m_CurrentTest = nullptr;
		}

		ImGui::End();

		if(m_CurrentTest != nullptr)
		{
			m_CurrentTest->OnImGuiRender();
		}
	}
}