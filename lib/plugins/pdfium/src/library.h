#pragma once

#include <mutex>

class Library
{
public:
    Library();
    ~Library();

    void Init();
    void Close();

    void lock(){
        bll_mutex.lock();
    }

    bool try_lock(){
        return bll_mutex.try_lock();
    }
    void unlock(){
        bll_mutex.unlock();
    }

private:
    std::mutex bll_mutex;
};
