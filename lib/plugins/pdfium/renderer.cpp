#include <renderer.h>
#include <imagetile.h>
#include <iinternallayout.h>
#include <irect.h>
#include <ilayout.h>
#include <fpdfview.h>


/**
flags -
    0 for normal display, or combination of flags defined below
    0x01 -  Set if annotations are to be rendered
    0x02 -  Set if using text rendering optimized for LCD display
    0x04 -  Set if you don't want to use GDI+ (Applicable to desktop Windows systems only)
    0x08 -  Grayscale output
    0x80 -  Set if you want to get some debug info.
    0x100 - Set if you don't want to catch exception

rotate - Page orientation: 0 (normal), 1 (rotated 90 degrees clockwise),
    2 (rotated 180 degrees), 3 (rotated 90 degrees counter-clockwise).
 */

Renderer::Renderer()
{
}

COM::HResult Renderer::QueryInterface(const std::string &id, void **ppv)
{
    if(id == RProto::IRenderer::iid){
        *ppv = (RProto::IRenderer*)this;
        return COM::HResult();
    }

    return COM::BaseComponent::QueryInterface(id, ppv);
}

RProto::IImageTile* Renderer::renderRect(RProto::IRect *rect)
{
    IInternalLayout *lay;
    auto err = rect->layout()->QueryInterface(IInternalLayout::iid, (void**)&lay);
    if(err.fail() || lay == nullptr)
        return nullptr;

    auto size = rect->layout()->pageSize(rect->page());
    ImageTile* tile = new ImageTile( rect->layout(), rect->page(), rect->zoom(),
                  rect->x(), rect->y(),
                  size.width(), size.height() );

    auto pdescr = lay->getPageDescr(rect->page());
    FPDF_RenderPageBitmap( tile->pdfBitmap(), pdescr.pdf_page,
                          rect->x(),  rect->y(),
                          size.width(), size.height(),
                          0/*rotate*/, 0x183 /*falgs*/);
    return tile;
}
