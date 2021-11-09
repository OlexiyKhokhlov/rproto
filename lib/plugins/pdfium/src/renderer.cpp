#include <util/singletone.h>
#include <renderer.h>
#include <imagetile.h>
#include <iinternallayout.h>
#include <irect.h>
#include <ilayout.h>
#include <book.h>
#include <fpdfview.h>
#include "library.h"

#include <assert.h>

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


/*
// Page rendering flags. They can be combined with bit OR.
#define FPDF_ANNOT			0x01		// Set if annotations are to be rendered.
#define FPDF_LCD_TEXT		0x02		// Set if using text rendering optimized for LCD display.
#define FPDF_NO_NATIVETEXT	0x04		// Don't use the native text output available on some platforms
#define FPDF_GRAYSCALE		0x08		// Grayscale output.
#define FPDF_DEBUG_INFO		0x80		// Set if you want to get some debug info.
                                        // Please discuss with Foxit first if you need to collect debug info.
#define FPDF_NO_CATCH		0x100		// Set if you don't want to catch exception.
#define FPDF_RENDER_LIMITEDIMAGECACHE	0x200	// Limit image cache size.
#define FPDF_RENDER_FORCEHALFTONE		0x400	// Always use halftone for image stretching.
#define FPDF_PRINTING		0x800	// Render for printing.
#define FPDF_REVERSE_BYTE_ORDER		0x10		//set whether render in a reverse Byte order, this flag only
                                                //enable when render to a bitmap.
*/

Renderer::Renderer(std::shared_ptr<Book> b)
    :bookOwner(b)
{
    assert(bookOwner != nullptr);
}

RProto::ImageTilePtrT Renderer::renderRect(RProto::IRectPtrT rect)
{
    auto pdf_page = bookOwner->getPage(rect->page());

    auto tile = std::make_shared<ImageTile>(rect->layout(), rect->page(), rect->zoom(),
                  rect->x()*rect->zoom(), rect->y()*rect->zoom(),
                  rect->width()*rect->zoom(), rect->height()*rect->zoom() );

    auto size = rect->layout()->pageSize(rect->page());
    auto zoom = rect->zoom();
    {
        std::scoped_lock<Library>  lock(Singletone<Library>::instance());
        FPDF_RenderPageBitmap( tile->pdfBitmap(), pdf_page->pdf_page,
                              0, 0,
                              size.first*zoom, size.second*zoom,
                              0/*rotate*/, /*0x183*/0x201/*falgs*/);
    }
    return tile;
}

RProto::ImageTilePtrT Renderer::renderThumbnail(RProto::IRectPtrT /*rect*/){
    return nullptr;
}
