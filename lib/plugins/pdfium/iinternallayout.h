#pragma once

#include <com/iunknown.h>
#include <fpdfview.h>

class IInternalLayout : public COM::IUnknown
{
public:
    struct PageDescriptor{
        FPDF_PAGE  pdf_page;
        double zoom;
    };

    virtual PageDescriptor& getPageDescr(int rpage=0) =0;
    //virtual

    static std::string iid;
};
