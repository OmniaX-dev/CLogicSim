#include "Board.hpp"
#include <ogfx/WindowBase.hpp>
#include <ostd/Signals.hpp>

void Board::init(void)
{
    enableSignals();
    connectSignal(ostd::tBuiltinSignals::MouseDragged);
    connectSignal(ostd::tBuiltinSignals::MouseMoved);
    connectSignal(ostd::tBuiltinSignals::MousePressed);
    connectSignal(ostd::tBuiltinSignals::MouseReleased);
}

void Board::render(ogfx::BasicRenderer2D& gfx)
{

}

void Board::handleSignal(ostd::tSignal& signal)
{
    if (signal.ID == ostd::tBuiltinSignals::MousePressed)
    {
        auto& mouseData = static_cast<ogfx::MouseEventData&>(signal.userData);
        if (mouseData.button == ogfx::MouseEventData::eButton::Middle)
        {
            m_panClicked = true;
            m_panClickPos = { (float)mouseData.position_x, (float)mouseData.position_y };
            return;
        }

    }
    else if (signal.ID == ostd::tBuiltinSignals::MouseReleased)
    {
        auto& mouseData = static_cast<ogfx::MouseEventData&>(signal.userData);
        if (mouseData.button == ogfx::MouseEventData::eButton::Middle)
        {
            m_panClicked = false;
        }

    }
    else if (signal.ID == ostd::tBuiltinSignals::MouseMoved)
    {
        auto& mouseData = static_cast<ogfx::MouseEventData&>(signal.userData);

    }
    else if (signal.ID == ostd::tBuiltinSignals::MouseDragged)
    {
        auto& mouseData = static_cast<ogfx::MouseEventData&>(signal.userData);
        if (mouseData.button == ogfx::MouseEventData::eButton::Middle)
        {
            if (!m_panClicked)
                return;
            ostd::Vec2 mousePos = { (float)mouseData.position_x, (float)mouseData.position_y };
            ostd::Vec2 posDiff = mousePos - m_panClickPos;

            m_panClickPos = mousePos;
        }
    }
}
