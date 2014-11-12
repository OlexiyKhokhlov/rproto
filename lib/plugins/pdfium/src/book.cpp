#include <book.h>
#include <assert.h>

#include <layout.h>
#include <renderer.h>

Book::Book(FPDF_DOCUMENT doc)
    :pdf_doc(doc)
    ,pageCache(1024*1024*128, 0.75f)
{}

Book::~Book()
{
    FPDF_CloseDocument(pdf_doc);
}

//Iunknown interface
COM::HResult Book::QueryInterface(const std::string& id, void** ppv)
{
    if(id == RProto::IBook::iid){
        *ppv = (RProto::IBook*)this;
        return COM::HResult();
    }

    return COM::BaseComponent::QueryInterface(id, ppv);
}

//IBook interface
RProto::ILayout* Book::createLayout(double dpix, double dpiy)
{
    return new Layout(this, dpix, dpiy);
}

RProto::IRenderer* Book::createRenderer()
{
    return new Renderer(this);
}
