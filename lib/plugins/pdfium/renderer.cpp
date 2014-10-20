#include "renderer.h"
#include <fpdfview.h>

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

void Renderer::renderRect(RProto::IRect *rect)
{
//    FPDF_RenderPageBitmap(FPDF_BITMAP bitmap, FPDF_PAGE page, int start_x,
//   int start_y, int size_x, int size_y, int rotate, int flags);

}
