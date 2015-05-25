#include <book.h>
#include <assert.h>
#include <core/base.h>
#include <fpdf_doc.h>

#include <layout.h>
#include <renderer.h>

#include <string>
#include <vector>
#include <utf8.h>

Book::Book(FPDF_DOCUMENT doc)
    :pdf_doc(doc)
    ,pageCache(sizeof(std::shared_ptr<Page>)*10, 0.75f) //10 pages max
{
    auto root = FPDFBookmark_GetFirstChild(pdf_doc, nullptr);
    auto b = root;
    while(b = FPDFBookmark_GetNextSibling(pdf_doc, b)){
        std::vector<unsigned short> utf16line(2048);
        auto len = FPDFBookmark_GetTitle(b, utf16line.data(), utf16line.size()*sizeof(unsigned short));
        if(len != 0){
            std::string utf8line;
            utf8::utf16to8(utf16line.begin(), utf16line.end(), back_inserter(utf8line));
            printf("%s\n", utf8line.c_str());
        }
    }

}

Book::~Book()
{
    pageCache.clear();
    FPDF_CloseDocument(pdf_doc);
}

//IBook interface
RProto::ILayout* Book::createLayout(double dpix, double dpiy)
{
    return Boss::Base<Layout>::CreatePtr(this, dpix, dpiy);
}

RProto::IRenderer* Book::createRenderer()
{
    return Boss::Base<Renderer>::CreatePtr(this);
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
