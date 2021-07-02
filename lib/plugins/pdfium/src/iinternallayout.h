#pragma once

#include <fpdfview.h>

class IInternalLayout
{
public:
    struct PageDescriptor{
        bool isValid;
        FPDF_PAGE  pdf_page;
        double zoom;
    };

    virtual PageDescriptor& getPageDescr(int rpage=0) =0;
};
