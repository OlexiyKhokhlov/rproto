#pragma once

#include <QSize>
#include <QString>
#include <iunknown.h>

class QObject;

namespace RProto {

class ILayout : public IUnknown
{
public:
  virtual ~ILayout(){}

  virtual int pages()const=0;
  virtual QSize pageSize(int rpage=0)=0;
  virtual void setViewportSize(const QSize& sz)=0;
  virtual QObject* qobject()=0;
};
}
