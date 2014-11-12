#pragma once

#include <mutex>

class Library
{
public:
    Library();
    ~Library();

    void Init();
    void Close();

    void BLL_lock(){
        bll_mutex.lock();
    }

    bool BLL_try_lock(){
        return bll_mutex.try_lock();
    }
    void BLL_unlock(){
        bll_mutex.unlock();
    }

private:
    std::mutex bll_mutex;
};
