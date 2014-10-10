#pragma once

#include <QRect>
#include <QObject>

#include <ilayout.h>
#include <baseobject.h>
#include <libdjvu/ddjvuapi.h>

namespace RProto{

class DjVuBook;

class DjVuPageLayout : public QObject, public BaseObject, public ILayout
{
    Q_OBJECT

public:
  DjVuPageLayout(DjVuBook *book, ddjvu_document_t* document, QObject *parent=nullptr);
  virtual ~DjVuPageLayout();

  //IUnknown
  virtual size_t addRef();
  virtual size_t release();
  virtual HResult queryInterface(const QUuid& iid, void** interface);

  //ILayout interface
  virtual void setViewportSize(const QSize& sz);
  virtual int pages()const;
  virtual QSize pageSize(int rpage=0);
  virtual QObject* qobject();

  void layoutChangedInternal(int,QSize);

signals:
    void layoutChanged(int,QSize);
  
private:
  DjVuBook  *owner;
  ddjvu_document_t*     djvu_document;
};
}
