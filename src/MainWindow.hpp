#pragma once

#include "BaseComponent.hpp"
#include <ogfx/BasicRenderer.hpp>

class MainWindow : public ogfx::WindowBase
{
	public:
		inline MainWindow(void) = default;
		void onInitialize(void) override;
		void onRender(void) override;
		void onUpdate(void) override;
		void handleSignal(ostd::tSignal& signal) override;

	private:
		BaseComponent test;
		BaseComponent test2;
        ogfx::BasicRenderer2D m_renderer2D;
};
