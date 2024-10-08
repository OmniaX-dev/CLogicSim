#include "BaseComponent.hpp"
#include <ogfx/BasicRenderer.hpp>
#include <ostd/Utils.hpp>

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
    m_backgroundColor = { 80, 10, 10, 200 }; 
    m_borderColor = { 230, 20, 20 };
    m_borderColorSelected = { 255, 150, 150 };
    m_textColor = { 230, 230, 230 };
    setID(BaseComponent::s_nextID++);
	return *this;
}

void BaseComponent::render(ogfx::BasicRenderer2D& gfx)
{
	gfx.fillRect(m_bounds, m_backgroundColor);
	gfx.drawRect(m_bounds, (m_selected ? m_borderColorSelected : m_borderColor), 1);
    gfx.drawCenteredString(toString(), m_bounds.getCenter(), m_textColor, 14);
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

ostd::String BaseComponent::toString(void) const
{
    return m_name + ":" + ostd::String("").add(getID());
}
