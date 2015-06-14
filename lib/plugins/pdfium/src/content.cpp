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
    if(pdf_doc != nullptr) loadContent();
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

const int Content::pageNumber(int subcontent_id, int row) const{
    auto item = getItem(subcontent_id, row);
    if(item == nullptr)
        return 0;
    return item->page;
}

std::pair<int,int> Content::parentId(int subcontent_id) const{
    if(subcontent_id >= (int)content.size())
        return std::make_pair(-1,-1);
    const SubContent& sc = content[subcontent_id];
    return std::make_pair(sc.parent_id, sc.parent_row);
}

int Content::childsId(int parent_id, int parent_row) const{
    return content[parent_id].items[parent_row].childs_id;
}

int Content::rowCount(int subcontent_id) const{
    if(subcontent_id >= (int)content.size())
        return 0;
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
    auto bookmark = FPDFBookmark_GetFirstChild(pdf_doc, nullptr);

    //empty content table
    if(bookmark == nullptr)return;

    content.emplace_back();
    SubContent* curr_content = &content.back();
    curr_content->parent_id = -1;
    curr_content->parent_row = -1;
    curr_content->items.reserve(32);

    int id  = 0;
    int row = 0;
    do{
        Item item;
        item.bookmark = bookmark;
        fillItem(item);
        curr_content->items.emplace_back(item);
        row = curr_content->items.size()-1;

        auto child = FPDFBookmark_GetFirstChild(pdf_doc, bookmark);
        if(child != nullptr){ //go to in the deep
            content.emplace_back();
            curr_content = &content.back();
            curr_content->parent_id = id;
            curr_content->parent_row = row;
            curr_content->items.reserve(32);
            id = content.size()-1;
            row = 0;
            bookmark = child;
            content[curr_content->parent_id].items[curr_content->parent_row].childs_id = id;
            continue;
        }

        bookmark = FPDFBookmark_GetNextSibling(pdf_doc, bookmark);
        if(bookmark != nullptr){  //traverse sibling
            continue;
        }

        if(curr_content->parent_id == -1 && bookmark == nullptr)
            break;

        //go to up!
        while(curr_content->parent_id != -1){
            curr_content->items.shrink_to_fit();
            id = curr_content->parent_id;
            row = curr_content->parent_row;
            curr_content = &content[id];
            auto item  = curr_content->items[row];
            bookmark = FPDFBookmark_GetNextSibling(pdf_doc, item.bookmark);
            if(bookmark != nullptr)
                break;
            id = -1;
        }

    }while(id != -1);
}

void Content::fillItem(Item& item){
    item.title.clear();
    item.page = 0;
    item.childs_id = -1;

    auto dest = FPDFBookmark_GetDest(pdf_doc, item.bookmark);
    if(dest != nullptr){
        item.page = FPDFDest_GetPageIndex(pdf_doc, dest);
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
