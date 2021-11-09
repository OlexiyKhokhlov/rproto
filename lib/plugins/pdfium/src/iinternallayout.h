#pragma once

#include <fpdfview.h>
#include <fpdf_doc.h>

#include <vector>

class IInternalLayout
{
public:
    struct Link {
        int         page = 0;
        FS_FLOAT    x    = 0.0;
        FS_FLOAT    y    = 0.0;
        FS_FLOAT    zoom = 1.0;
        FS_RECTF    rect = {0.0, 0.0, 0.0, 0.0};
    };

    struct PageDescriptor{
        double     zoom;
        std::vector<Link> links;
    };

    virtual PageDescriptor& getPageDescr(int rpage=0) =0;
};
