#pragma once

#include <core/ibase.h>
#include <fpdfview.h>

class IInternalLayout : public Boss::Inherit<Boss::IBase>
{
public:
    BOSS_DECLARE_IFACEID("PDFIUM.IInternalLayout")

    struct PageDescriptor{
        bool isValid;
        FPDF_PAGE  pdf_page;
        double zoom;
    };

    virtual PageDescriptor& getPageDescr(int rpage=0) =0;
};
