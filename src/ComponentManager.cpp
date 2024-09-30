#include "ComponentManager.hpp"
#include <memory>
#include <ogfx/BasicRenderer.hpp>
#include <ostd/Signals.hpp>
#include <ostream>

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
    }
    else if (signal.ID == ostd::tBuiltinSignals::MouseDragged)
    {
        if (hasSelected())
        {
            m_selectedComponent->handleSignal(signal);
        }
    }
    else if (signal.ID == ostd::tBuiltinSignals::MouseReleased)
    {
        if (hasSelected())
        {
            m_selectedComponent->handleSignal(signal);
        }
    }
    
}

void ComponentManager::selectComponent(int32_t index)
{
    if (index < 0 || index >= m_components.size())
    {
        m_selectedComponent = nullptr;
        return;
    }
    for (auto& component : m_components)
        component->select(false);
    m_selectedComponent = m_components[index];
    m_selectedComponent->select(true);
    m_selectedIndex = index;
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

