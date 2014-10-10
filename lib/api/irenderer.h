#pragma once

#include <QRect>
#include <QImage>
#include <QColor>

#include <iunknown.h>

namespace RProto {

class IAsyncRenderer : public IUnknown
{
public:
  virtual ~IAsyncRenderer(){}
  
  virtual QImage renderRect(int rpage=0, QRect rect=QRect(), float scale=1.0)=0;
};
}
