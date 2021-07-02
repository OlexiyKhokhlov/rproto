#pragma once

#include <baserect.h>

class Rect : public RProto::BaseRect
{
public:
    Rect(RProto::ILayoutPtrT lay, int page, double zoom, int x, int y, int width, int height)
        :BaseRect(lay, page, zoom, x, y, width, height)
    {}
};
