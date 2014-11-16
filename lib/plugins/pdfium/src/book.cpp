#include <book.h>
#include <assert.h>

#include <layout.h>
#include <renderer.h>

Book::Book(FPDF_DOCUMENT doc)
    :pdf_doc(doc)
    ,pageCache(sizeof(std::shared_ptr<Page>)*10, 0.75f) //10 pages max
{}

Book::~Book()
{
    pageCache.clear();
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

std::shared_ptr<Book::Page> Book::getPage(int num){
    cacheMutex.lock();

    auto it = pageCache.map_find(num);
    if(it != pageCache.map_end()){
        pageCache.touch(it->second.second);
        cacheMutex.unlock();
        return it->second.first;
    }

    std::shared_ptr<Book::Page> pg(new Page(pdf_doc, num));
    pageCache.push_front(num, pg);

    cacheMutex.unlock();
    return pg;
}
