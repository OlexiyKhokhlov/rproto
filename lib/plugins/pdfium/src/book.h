#include <ibook.h>
#include <imagetile.h>
#include <library.h>

#include <util/rlucache.h>
#include <util/singletone.h>

#include <core/co_class.h>

#include <fpdfview.h>

#include <memory>
#include <thread>

template<>
struct Weight<ImageTilePtr>{
    int operator()(ImageTilePtr const& v){
        return v->rect()->page();
    }
};

class Book : public Boss::CoClass<Boss::MakeId("PDFium.Book"), RProto::IBook>
{
public:
    Book(FPDF_DOCUMENT doc);
    virtual ~Book();

    //IBook interface
    virtual RProto::ILayout* createLayout(double dpix, double dpiy) override;
    virtual RProto::IRenderer* createRenderer() override;

    //Plugin private
    struct Page{
        explicit Page(FPDF_DOCUMENT doc, int  num){
            Singletone<Library>::instance().BLL_lock();
            pdf_page = FPDF_LoadPage(doc, num);
            Singletone<Library>::instance().BLL_unlock();
        }

        ~Page(){
            Singletone<Library>::instance().BLL_lock();
            FPDF_ClosePage(pdf_page);
            Singletone<Library>::instance().BLL_unlock();
        }

        FPDF_PAGE pdf_page;
    };

    FPDF_DOCUMENT document(){
        return pdf_doc;
    }

     std::shared_ptr<Page> getPage(int num);

private:
    FPDF_DOCUMENT pdf_doc;

    std::mutex cacheMutex;
    RLUCache<int, std::shared_ptr<Page> >  pageCache;
};
