#pragma once

#include "Global.hpp"
#include <ogfx/BasicRenderer.hpp>
#include <ostd/Color.hpp>

class BaseComponent : public Drawable
{
	public:
		BaseComponent(void);
		BaseComponent(ogfx::WindowBase& window);
		BaseComponent& init(ogfx::WindowBase& window);
		virtual void render(ogfx::BasicRenderer2D& gfx) override;
		virtual void update(void);
		bool isMouseInside(void);
		virtual void handleSignal(ostd::tSignal& signal) override;
        inline void select(bool s = true) { m_selected = s; }
        inline bool isSelected(void) const { return m_selected; }
        ostd::String toString(void) const override;
        inline void setName(const ostd::String& name) { m_name = name; }
        inline ostd::String getName(void) const { return m_name; }

	protected:
        bool m_selected { false };
        ostd::String m_name { "BASE_C" };

	private:
		ostd::Vec2 m_mousePos;
		ostd::Vec2 m_pressPoint;
		bool m_mousePressedInside { false };

        ostd::Color m_borderColor;
        ostd::Color m_borderColorSelected;
        ostd::Color m_backgroundColor;
        ostd::Color m_textColor;

        inline static int32_t s_nextID = { 1024 }; 
};
