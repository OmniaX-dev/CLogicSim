#include "BaseComponent.hpp"
#include <ogfx/BasicRenderer.hpp>

BaseComponent::BaseComponent(void)
{

}

BaseComponent::BaseComponent(ogfx::WindowBase& window)
{
	init(window);
}

BaseComponent& BaseComponent::init(ogfx::WindowBase& window)
{
	m_bounds = { 30, 30, 120, 60 };

    setID(BaseComponent::s_nextID++);
	// enableSignals();
	// connectSignal(ostd::tBuiltinSignals::MousePressed);
	// connectSignal(ostd::tBuiltinSignals::MouseReleased);
	// connectSignal(ostd::tBuiltinSignals::MouseMoved);
	// connectSignal(ostd::tBuiltinSignals::MouseDragged);
	return *this;
}

void BaseComponent::render(ogfx::BasicRenderer2D& gfx)
{
    ostd::Color borderColor = (m_selected ? ostd::Color { 200, 150, 200 } : ostd::Color { 200, 20, 20 });
	gfx.outlinedRect(m_bounds, { 200, 20, 20, 40 }, borderColor, 2);
}

void BaseComponent::update(void)
{
}

bool BaseComponent::isMouseInside(void)
{
	return m_bounds.contains(m_mousePos);
}

void BaseComponent::handleSignal(ostd::tSignal& signal)
{
	if (signal.ID == ostd::tBuiltinSignals::MouseMoved)
	{
		auto& mouseData = static_cast<ogfx::MouseEventData&>(signal.userData);
		m_mousePos = { (float)mouseData.position_x, (float)mouseData.position_y };
	}
	else if (signal.ID == ostd::tBuiltinSignals::MousePressed)
	{
		auto& mouseData = static_cast<ogfx::MouseEventData&>(signal.userData);
		if (isMouseInside())
		{
			m_pressPoint = ostd::Vec2 { (float)mouseData.position_x, (float)mouseData.position_y } - m_bounds.getPosition();
			m_mousePressedInside = true;
		}
	}
	else if (signal.ID == ostd::tBuiltinSignals::MouseReleased)
	{
		auto& mouseData = static_cast<ogfx::MouseEventData&>(signal.userData);
		m_mousePressedInside = false;
	}
	else if (signal.ID == ostd::tBuiltinSignals::MouseDragged)
	{
		auto& mouseData = static_cast<ogfx::MouseEventData&>(signal.userData);
		m_mousePos = { (float)mouseData.position_x, (float)mouseData.position_y };
		if (m_mousePressedInside)
			m_bounds.setPosition(m_mousePos - m_pressPoint);
	}
}
