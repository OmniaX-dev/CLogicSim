#pragma once

#include "BaseComponent.hpp"
#include <ogfx/BasicRenderer.hpp>
#include <ostd/BaseObject.hpp>
#include <ostd/Signals.hpp>
#include <vector>

class ComponentManager : public ostd::BaseObject
{
    public:
        static ComponentManager& instance(void);
        void update(void);
        void render(ogfx::BasicRenderer2D& gfx);
        bool addComponent(BaseComponent& compoent);
        void handleSignal(ostd::tSignal& signal);

        void selectComponent(int32_t index);
        void drawSelectedBorder(ogfx::BasicRenderer2D& gfx);

        inline bool hasSelected(void) const { return m_selectedComponent != nullptr && m_selectedIndex >= 0 && m_selectedIndex < m_components.size() && m_components.size() > 0; }

    private:
        ComponentManager(void);
        bool compoent_exists(BaseComponent& component);

    private:
        std::vector<BaseComponent*> m_components;
        BaseComponent* m_selectedComponent { nullptr };
        int32_t m_selectedIndex { -1 };
        ostd::Vec2 m_panClickPos { 0, 0 };
        bool m_panClicked { false };

        ostd::Color m_selectedBorderColor { 20, 150, 180 };
};
