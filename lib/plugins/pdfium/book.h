#include <com/basecomponent.h>
#include <ibook.h>
#include <fpdfview.h>

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
    virtual RProto::ILayout* createLayout() override;
    virtual RProto::IRenderer* createRenderer() override;

    //Plugin private
    FPDF_DOCUMENT document(){
        return pdf_doc;
    }

private:
    FPDF_DOCUMENT pdf_doc;
};