#include "MainWindow.hpp"
#include "ComponentManager.hpp"
#include <ogfx/Image.hpp>

void MainWindow::onInitialize(void)
{
	test.init(*this);
	test2.init(*this);
    test2.bounds().setPosition({ 400, 120 });
	enableSignals();
	connectSignal(ostd::tBuiltinSignals::KeyReleased);
	enableMouseDragEvent();
	m_renderer2D.init(*this);
	m_renderer2D.setFont("res/ttf/Courier Prime.ttf");
    ComponentManager::instance().addComponent(test);
    ComponentManager::instance().addComponent(test2);
    m_mainBoard.init(m_renderer2D);
}	

void MainWindow::onRender(void)
{
    m_mainBoard.render(m_renderer2D);
    ComponentManager::instance().render(m_renderer2D);
}

void MainWindow::onUpdate(void)
{
    ComponentManager::instance().update();
}

void MainWindow::handleSignal(ostd::tSignal& signal)
{
	if (signal.ID == ostd::tBuiltinSignals::KeyReleased)
	{
		auto& keyData = static_cast<ogfx::KeyEventData&>(signal.userData);
		if (keyData.keyCode == SDLK_ESCAPE)
		{
			close();
		}
	}
}
