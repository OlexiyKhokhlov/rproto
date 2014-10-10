#pragma once

#include <boost/detail/atomic_count.hpp>

namespace RProto{

class BaseObject
{
public:
    BaseObject():ref(0){}

protected:
    virtual size_t internalAddRef(){
        return ++ref;
    }

    virtual size_t internalRelease(){
        return --ref;
    }

private:
    boost::detail::atomic_count ref;
};

}
