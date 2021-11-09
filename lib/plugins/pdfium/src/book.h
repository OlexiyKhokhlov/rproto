#pragma once

#include <forward.h>
#include <ibook.h>
#include <library.h>
#include <content.h>
#include <renderer.h>
#include <imagetile.h>

#include <util/rlucache.h>
#include <util/singletone.h>

#include <fpdfview.h>

#include <memory>
#include <thread>

template<>
struct Weight<RProto::ImageTilePtrT>{
    int operator()(RProto::ImageTilePtrT const& v){
        return v->rect()->page();
    }
};

class Book : public RProto::IBook, public std::enable_shared_from_this<Book>
{
public:
    Book(FPDF_DOCUMENT doc);
    virtual ~Book();

    //IBook interface
    RProto::ILayoutPtrT createLayout(double dpix, double dpiy) override;
    RProto::IRendererPtrT createRenderer() override;
    RProto::IContentPtrT createContent() override;

    //Plugin private
    FPDF_DOCUMENT document() {
        return pdf_doc;
    }

    struct Page {
        Page(FPDF_PAGE page)
            : pdf_page (page)
        {}
        ~Page() {
            std::scoped_lock<Library>  lock(Singletone<Library>::instance());
            FPDF_ClosePage(pdf_page);
        }
        FPDF_PAGE pdf_page = nullptr;
    };

    std::shared_ptr<Page> getPage(int num);

private:
    FPDF_DOCUMENT pdf_doc;

    std::mutex cacheMutex;
    RLUCache<int, std::shared_ptr<Page>>  pageCache;
};
