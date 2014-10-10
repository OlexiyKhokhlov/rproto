#pragma once

#include <irenderer.h>
#include <baseobject.h>
#include <libdjvu/ddjvuapi.h>

namespace RProto{
class IBook;

class DjVuRenderer : public QObject, public BaseObject, public IAsyncRenderer
{
    Q_OBJECT
public:
    DjVuRenderer(IBook* book, ddjvu_document_t* document);
    virtual ~DjVuRenderer();

    //IUnknown
    virtual size_t addRef();
    virtual size_t release();
    virtual HResult queryInterface(const QUuid& iid, void** interface);
  
    //IRenderer interface
    virtual QImage renderRect(int rpage=0, QRect rect=QRect(), float scale=1.0);

signals:
    void updateScreen(QImage,QRect, int page, float scale);

public slots:
    void redisplay(const ddjvu_message_redisplay_s *);
  
private:
  IBook*    owner;
  ddjvu_document_t* djvu_document;
  ddjvu_format_t*	djvu_format;
};
}
