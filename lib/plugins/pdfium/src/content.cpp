#include "content.h"
#include <fpdf_doc.h>
#include <string>
#include <vector>
#include <utf8.h>

std::string Content::empty;

Content::Content(FPDF_DOCUMENT doc)
    :pdf_doc(doc)
    ,listener(nullptr)
{

}

Content::~Content(){

}

//Interface IContent
void Content::addListener(RProto::IContentListener *lst){
    listener = lst;
}

const std::string& Content::title(int subcontent_id, int row) const{
    auto item = getItem(subcontent_id, row);
    if(item == nullptr)
        return empty;
    return item->title;
}

const std::string& Content::link(int subcontent_id, int row) const{
    auto item = getItem(subcontent_id, row);
    if(item == nullptr)
        return empty;
    return item->link;
}

std::pair<int,int> Content::parentId(int subcontent_id) const{
    return std::make_pair(0,0);
}

int Content::rowCount(int subcontent_id) const{
    if(subcontent_id >= (int)content.size())
        return -1;
    return content[subcontent_id].items.size();
}

const Content::Item* Content::getItem(int subcontent_id, int row) const{
    if(subcontent_id >= (int)content.size())
        return nullptr;
    const SubContent& sc = content[subcontent_id];
    if(row >= (int)sc.items.size())
        return nullptr;

    return &(sc.items[row]);
}

void Content::loadContent(){
    auto node = FPDFBookmark_GetFirstChild(pdf_doc, nullptr);

    if(node == nullptr){
        //empty content table
        return;
    }

}

void Content::fillSubContent(SubContent& sc, FPDF_BOOKMARK first){
    sc.items.clear();
    if(first == nullptr)
        return;

    sc.items.reserve(32);
    do{
        Item item;
        item.bookmark = first;
        fillItem(item);
        sc.items.emplace_back(item);
    }while((first = FPDFBookmark_GetNextSibling(pdf_doc, first)) != nullptr);
    sc.items.shrink_to_fit();
}

void Content::fillItem(Item& item){
    item.title.clear();
    item.link.clear();

    auto dest = FPDFBookmark_GetDest(pdf_doc, item.bookmark);
    if(dest != nullptr){
        auto page = FPDFDest_GetPageIndex(pdf_doc, dest);
        item.link = std::to_string(page);
    }

    std::vector<unsigned short> utf16line(256);
    auto len = FPDFBookmark_GetTitle(item.bookmark, utf16line.data(), utf16line.size()*sizeof(unsigned short));
//    if(len == 0){
//        len = FPDFBookmark_GetPageFirstLine(page, utf16line.data(), utf16line.size()*sizeof(unsigned short));
//    }
    if(len != 0){
        utf8::utf16to8(utf16line.begin(), utf16line.end(), back_inserter(item.title));
    }
}
