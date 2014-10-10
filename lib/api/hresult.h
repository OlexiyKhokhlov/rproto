#pragma once

#include <QtCore>

namespace RProto {
class HResult
{
public:
   inline HResult(bool err, quint32 code){
        value=code;
        if(err){
            value |= (31<<1);
        }else{
            value &= (31<<1);
        }
    }

    inline bool fail(){
        return value|(1<<31) == 0? false : true;
    }

    inline bool success(){
        return !fail();
    }

    inline quint32 code(){
        return value & ~(1<<31);
    }

private:
    quint32 value;
};

}
