#pragma once
#include <mutex>

class MutEX
{
private:
    std::mutex mtx;
public:
    MutEX()
    {
        mtx.lock();
    }

    ~MutEX()
    {
        mtx.unlock();
    }
};