#pragma once

#include <ostd/BaseObject.hpp>
#include <ostd/Color.hpp>
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

class Utils
{
    public:
        static void drawCornerRect(ogfx::BasicRenderer2D& gfx, const ostd::Rectangle& rect, const ostd::Color& color, int32_t thickness, int32_t segmentLength);
};
