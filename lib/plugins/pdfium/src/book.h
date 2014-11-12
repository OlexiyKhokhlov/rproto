#include <com/basecomponent.h>
#include <util/rlucache.h>
#include <ibook.h>
#include <fpdfview.h>
#include <imagetile.h>

template<>
struct Weight<ImageTilePtr>{
    int operator()(ImageTilePtr const& v){
        return v->rect()->page();
    }
};

class Book : public COM::BaseComponent, public RProto::IBook
{
public:
    Book(FPDF_DOCUMENT doc);
    virtual ~Book();

    //Iunknown interface
    virtual COM::HResult QueryInterface(const std::string& id, void** ppv) override;
    virtual int addRef(){
        return COM::BaseComponent::addRef();
    }
    virtual int release() {
        return COM::BaseComponent::release();
    }

    //IBook interface
    virtual RProto::ILayout* createLayout(double dpix, double dpiy) override;
    virtual RProto::IRenderer* createRenderer() override;

    //Plugin private
    FPDF_DOCUMENT document(){
        return pdf_doc;
    }

//    RLUCache<ImageTilePtr>* cache(){
//        return &pageCache;
//    }

private:
    FPDF_DOCUMENT pdf_doc;

    RLUCache<int, ImageTilePtr>  pageCache;
};
