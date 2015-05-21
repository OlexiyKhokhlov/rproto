#pragma once

#include <atomic>

class RefObject
{
public:
    RefObject():ref(0){}
    virtual ~RefObject(){}

    inline unsigned int add_ref(){
        return ++ref;
    }

    inline unsigned int release(){
        return --ref;
    }

private:
    std::atomic_int_fast32_t ref;
};

namespace boost {
    inline void intrusive_ptr_add_ref(RefObject* ptr){
        ptr->add_ref();
    }

    inline void intrusive_ptr_release(RefObject* ptr){
        if(!ptr->release())
            delete ptr;
    }
}//namespace boost
