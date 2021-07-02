#pragma once

template <class T>
class Singletone{
public:
    static T& instance(){
        static T inst;
        return inst;
    }

};
