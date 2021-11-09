#include <book.h>
#include <assert.h>
#include <fpdf_doc.h>

#include <layout.h>
#include <renderer.h>
#include <content.h>

Book::Book(FPDF_DOCUMENT doc)
    : pdf_doc(doc)
    , pageCache(sizeof(std::shared_ptr<Page>)*10, 0.75f) //10 pages max
{
    assert(pdf_doc);
}

Book::~Book() {
    pageCache.clear();
    {
        std::scoped_lock<Library>  lock(Singletone<Library>::instance());
        FPDF_CloseDocument(pdf_doc);
    }
}

//IBook interface
RProto::ILayoutPtrT Book::createLayout(double dpix, double dpiy)
{
    return std::make_shared<Layout>(shared_from_this(), dpix, dpiy);
}

RProto::IRendererPtrT Book::createRenderer()
{
    return std::make_shared<Renderer>(shared_from_this());
}

RProto::IContentPtrT Book::createContent(){
    return std::make_shared<Content>(pdf_doc);
}

std::shared_ptr<Book::Page> Book::getPage(int num){
    std::scoped_lock<std::mutex> lock(cacheMutex);

    auto it = pageCache.map_find(num);
    if(it != pageCache.map_end()){
        pageCache.touch(it->second.second);
        return it->second.first;
    }

    std::shared_ptr<Page> page;
    {
        std::scoped_lock<Library>  lock(Singletone<Library>::instance());
        page = std::make_shared<Page>(FPDF_LoadPage(pdf_doc, num));
    }
    pageCache.push_front(num, page);

    return page;
}
