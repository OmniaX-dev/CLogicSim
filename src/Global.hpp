#pragma once

#include <ostd/BaseObject.hpp>
#include <ostd/Geometry.hpp>
#include <ogfx/BasicRenderer.hpp>
#include <ogfx/WindowBase.hpp>
#include <ostd/IOHandlers.hpp>

class Drawable : public ostd::BaseObject
{
	public:
		virtual void render(ogfx::BasicRenderer2D&) = 0;
        inline ostd::Rectangle& bounds(void) { return m_bounds; }

	protected:
		ostd::Rectangle m_bounds;
};
