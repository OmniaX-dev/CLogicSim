#include "ComponentManager.hpp"
#include <ogfx/BasicRenderer.hpp>
#include <ostd/Signals.hpp>

ComponentManager& ComponentManager::instance(void)
{
    static ComponentManager cm;
    return cm;
}

void ComponentManager::update(void)
{
    for (auto& component : m_components)
    {
        component->update();
    }
}

void ComponentManager::render(ogfx::BasicRenderer2D& gfx)
{
    for (auto& component : m_components)
    {
        component->render(gfx);
    }
    drawSelectedBorder(gfx);
}

bool ComponentManager::addComponent(BaseComponent& component)
{
    if (!compoent_exists(component))
        m_components.push_back(&component);
    m_selectedComponent = &component;
    return true;
}

void ComponentManager::handleSignal(ostd::tSignal& signal)
{
    if (m_components.size() == 0)
        return;
    if (signal.ID == ostd::tBuiltinSignals::MouseMoved)
    {
        
        for (auto& component : m_components)
            component->handleSignal(signal);
    }
    else if (signal.ID == ostd::tBuiltinSignals::MousePressed)
    {
        auto& mouseData = static_cast<ogfx::MouseEventData&>(signal.userData);
        if (mouseData.button == ogfx::MouseEventData::eButton::Middle)
        {
            m_panClicked = true;
            m_panClickPos = { (float)mouseData.position_x, (float)mouseData.position_y };
            return;
        }

        int32_t index = m_components.size() - 1;
        bool found = false;
        for ( ; index >= 0; index--)
        {
            if (m_components[index]->isMouseInside())
            {
                found = true;
                break;
            }
        }
        if (found)
        {
            selectComponent(index);
            m_components.erase(m_components.begin() + index);
            m_components.push_back(m_selectedComponent);
        }
        else
        {
            selectComponent(-1);
            return;
        }
        if (hasSelected())
        {
            m_selectedComponent->handleSignal(signal);
        }
    }
    else if (signal.ID == ostd::tBuiltinSignals::MouseDragged)
    {
        auto& mouseData = static_cast<ogfx::MouseEventData&>(signal.userData);
        if (mouseData.button == ogfx::MouseEventData::eButton::Middle)
        {
            if (!m_panClicked)
                return;
            ostd::Vec2 mousePos = { (float)mouseData.position_x, (float)mouseData.position_y };
            for (auto& component : m_components)
            {
                component->bounds().addPos(mousePos - m_panClickPos);
            }
            m_panClickPos = mousePos;
        }
        else if (mouseData.button == ogfx::MouseEventData::eButton::Left)
        {
            if (hasSelected())
            {
                m_selectedComponent->handleSignal(signal);
            }
        }
    }
    else if (signal.ID == ostd::tBuiltinSignals::MouseReleased)
    {
        auto& mouseData = static_cast<ogfx::MouseEventData&>(signal.userData);
        if (mouseData.button == ogfx::MouseEventData::eButton::Middle)
        {
            m_panClicked = false;
        }
        else if (hasSelected())
        {
            m_selectedComponent->handleSignal(signal);
        }
    }
    
}

void ComponentManager::selectComponent(int32_t index)
{
    if (index < 0 || index >= m_components.size())
    {
        for (auto& component : m_components)
            component->select(false);
        m_selectedComponent = nullptr;
        return;
    }
    for (auto& component : m_components)
        component->select(false);
    m_selectedComponent = m_components[index];
    m_selectedComponent->select(true);
    m_selectedIndex = index;
}

void ComponentManager::drawSelectedBorder(ogfx::BasicRenderer2D& gfx)
{
    if (!hasSelected())
        return;
    auto bounds = m_selectedComponent->bounds();
    int32_t segmentLength = 20;
    int32_t padding = 10;
    bounds.x -= padding;
    bounds.y -= padding;
    bounds.w += (padding * 2);
    bounds.h += (padding * 2);
    Utils::drawCornerRect(gfx, bounds, m_selectedBorderColor, 2, segmentLength);
}


ComponentManager::ComponentManager(void)
{
    connectSignal(ostd::tBuiltinSignals::MousePressed);
	connectSignal(ostd::tBuiltinSignals::MouseReleased);
	connectSignal(ostd::tBuiltinSignals::MouseMoved);
	connectSignal(ostd::tBuiltinSignals::MouseDragged);

    enableSignals();
    validate();
}

bool ComponentManager::compoent_exists(BaseComponent& component)
{
    for (auto& c : m_components)
    {
        if (c->getID() == component.getID())
            return true;
    }
    return false;
}

