#pragma once

#include <basepoint.h>

class Point : public RProto::BasePoint
{
public:
    Point(RProto::ILayout *lay, int page, double zoom, int x, int y)
        :BasePoint(lay, page, zoom, x, y)
    {}
};
