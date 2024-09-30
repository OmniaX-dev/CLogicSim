#include "Global.hpp"
#include <ogfx/BasicRenderer.hpp>

void Utils::drawCornerRect(ogfx::BasicRenderer2D& gfx, const ostd::Rectangle& rect, const ostd::Color& color, int32_t thickness, int32_t segmentLength)
{
    if (!gfx.isInitialized())
        return;
    gfx.drawLine({ rect.x, rect.y, rect.x + segmentLength, rect.y }, color, thickness);
    gfx.drawLine({ rect.x, rect.y, rect.x, rect.y + segmentLength }, color, thickness);

    gfx.drawLine({ rect.x, rect.y + segmentLength, rect.x, rect.y }, color, thickness);
    gfx.drawLine({ rect.x, rect.y, rect.x + segmentLength, rect.y }, color, thickness);

    gfx.drawLine({ (rect.x + rect.w) - segmentLength, (rect.y + rect.h), (rect.x + rect.w), (rect.y + rect.h) }, color, thickness);
    gfx.drawLine({ (rect.x + rect.w), (rect.y + rect.h) - segmentLength, (rect.x + rect.w), (rect.y + rect.h) }, color, thickness);

    gfx.drawLine({ (rect.x + rect.w) - segmentLength, rect.y, (rect.x + rect.w), rect.y }, color, thickness);
    gfx.drawLine({ (rect.x + rect.w), rect.y, (rect.x + rect.w), rect.y + segmentLength }, color, thickness);
}
