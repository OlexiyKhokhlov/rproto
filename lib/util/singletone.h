#pragma once

template <class T>
class Singletone{
public:
    static T& instance(){
        T *inst = nullptr;
        if(inst == nullptr){
            inst = new T();
        }

        return *inst;
    }

};
