#pragma once

#include <ogfx/Image.hpp>
#include <ogfx/BasicRenderer.hpp>
#include <ostd/BaseObject.hpp>
#include <ostd/Geometry.hpp>

class Board : public ostd::BaseObject
{
    public:
        inline Board(void) { invalidate(); }
        inline Board(ogfx::BasicRenderer2D& gfx) { init(gfx); }
        void init(ogfx::BasicRenderer2D& gfx);
        void render(ogfx::BasicRenderer2D& gfx);
        void handleSignal(ostd::tSignal& signal) override;

    private:
        ogfx::Image m_gridImg;
        bool m_panClicked { false };
        ostd::Vec2 m_panClickPos;
        ostd::Vec2 m_gridPos;
};
