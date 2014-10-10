#pragma once

#include <hresult.h>
#include <QUuid>

namespace RProto{

class IUnknown
{
public:
    virtual ~IUnknown(){}

    virtual size_t addRef()=0;
    virtual size_t release()=0;
    virtual RProto::HResult queryInterface(const QUuid& iid, void** interface)=0;
};

}

namespace boost {
    inline void intrusive_ptr_add_ref(RProto::IUnknown* ptr){
        ptr->addRef();
    }

    inline void intrusive_ptr_release(RProto::IUnknown* ptr){
        if(!ptr->release())
            delete ptr;
    }
}//namespace boost

#include <boost/intrusive_ptr.hpp>
