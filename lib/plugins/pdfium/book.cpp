#include <book.h>
#include <assert.h>

Book::Book(FPDF_DOCUMENT doc)
    :pdf_doc(doc)
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
RProto::ILayout* Book::createLayout()
{
    return nullptr;
}

RProto::IRenderer* Book::createRenderer()
{
    return nullptr;
}
