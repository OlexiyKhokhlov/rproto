#pragma once

#include <ilayout.h>
#include <libdjvu/ddjvuapi.h>

class DjVuBook;

class DjVuPageLayout : public COM::BaseComponent, public RProto::ILayout
{
public:
  DjVuPageLayout(DjVuBook *book, ddjvu_document_t* document);
  virtual ~DjVuPageLayout();

  //Iunknown interface
  virtual COM::HResult QueryInterface(const std::string& id, void** ppv) override;
  virtual int addRef(){
      return COM::BaseComponent::addRef();
  }
  virtual int release() {
      return COM::BaseComponent::release();
  }

  //ILayout interface
  virtual void addListener(RProto::ILayoutListener *listener) override;
  virtual RProto::IBook* book() override;
  virtual void startLayouting() override;
  virtual void cancelLayouting() override;
  virtual int pages()const override;
  virtual std::pair<int,int> pageSize(int rpage=0)const override;
  virtual double pageZoom(int rpage=0)const override;
  virtual void setPageZoom(int rpage=0, double zoom=1) override;
  virtual void setDocumentZoom(double zoom=1) override;
  virtual RProto::IPoint* createPoint(int rpage, int x, int y)const override;
  //TODO create a point by link
  //virtual IPoint* createPoint(ILink *link)const override;
  virtual RProto::IRect* createRect(int rpage, int x, int y, int width, int height)const override;

  //void layoutChangedInternal(int,QSize);

private:
  DjVuBook  *owner;
  ddjvu_document_t*     djvu_document;
  RProto::ILayoutListener *listenerPtr;
};
