#pragma once

#include <iunknown.h>

namespace RProto{

class ILayout;
class IAsyncRenderer;

class IBook : public IUnknown
{
public:
    virtual ~IBook(){}

    virtual boost::intrusive_ptr<ILayout> createLayout() =0;
    virtual boost::intrusive_ptr<IAsyncRenderer> createRenderer() =0;
};
}
