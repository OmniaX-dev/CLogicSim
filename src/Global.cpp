#include "Global.hpp"
#include <ogfx/BasicRenderer.hpp>

void Utils::drawCornerRect(ogfx::BasicRenderer2D& gfx, const ostd::Rectangle& rect, const ostd::Color& color, int32_t thickness, int32_t segmentLength)
{
    if (!gfx.isInitialized())
        return;

    //TOP LEFT
    gfx.drawLine({ rect.x, rect.y, rect.x + segmentLength, rect.y }, color, thickness);
    gfx.drawLine({ rect.x, rect.y, rect.x, rect.y + segmentLength }, color, thickness);

    //BOTTOM LEFT
    gfx.drawLine({ rect.x, (rect.y + rect.h) - segmentLength, rect.x, (rect.y + rect.h) }, color, thickness);
    gfx.drawLine({ rect.x, (rect.y + rect.h), rect.x + segmentLength, (rect.y + rect.h) }, color, thickness);

    //BOTTOM RIGHT
    gfx.drawLine({ (rect.x + rect.w) - segmentLength, (rect.y + rect.h), (rect.x + rect.w), (rect.y + rect.h) }, color, thickness);
    gfx.drawLine({ (rect.x + rect.w), (rect.y + rect.h) - segmentLength, (rect.x + rect.w), (rect.y + rect.h) }, color, thickness);

    //TOP RIGHT
    gfx.drawLine({ (rect.x + rect.w) - segmentLength, rect.y, (rect.x + rect.w), rect.y }, color, thickness);
    gfx.drawLine({ (rect.x + rect.w), rect.y, (rect.x + rect.w), rect.y + segmentLength }, color, thickness);
}
