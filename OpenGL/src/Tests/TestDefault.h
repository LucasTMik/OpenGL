#pragma once

#include "Test.h"
#include <vector>
#include <memory>

	
namespace Test {
	class TestDefault : public Test
	{
	public:
		TestDefault();
		~TestDefault();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		std::shared_ptr<Test> m_CurrentTest;
	};
}