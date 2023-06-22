#include "JobManagement.hpp"

namespace FantasyGameEngine
{
    BasicThreadPool::BasicThreadPool(size_t numThreads) : stop(false)
    {
        for (size_t i = 0; i < numThreads; ++i) {
            threads.emplace_back([this] {
                while (true) {
                    std::function<void()> task;

                    {
                        std::unique_lock<std::mutex> lock(queueMutex);
                        condition.wait(lock, [this] { return stop || !taskQueue.empty(); });

                        if (stop && taskQueue.empty())
                            return;

                        task = std::move(taskQueue.front());
                        taskQueue.pop();
                    }

                    task();
                }
                });
        }
    }

    BasicThreadPool::~BasicThreadPool()
    {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            stop = true;
        }

        condition.notify_all();

        for (std::thread& thread : threads)
            thread.join();
    }
}