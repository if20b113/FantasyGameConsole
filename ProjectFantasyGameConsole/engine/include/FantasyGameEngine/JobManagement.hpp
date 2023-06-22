#pragma once

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>

namespace FantasyGameEngine
{
    class BasicThreadPool
    {
    public:
        BasicThreadPool(size_t numThreads);

        ~BasicThreadPool();

        template<typename Func, typename... Args>
        auto enqueue(Func&& func, Args&&... args) -> std::future<typename std::result_of<Func(Args...)>::type>
        {
            using ReturnType = typename std::result_of<Func(Args...)>::type;

            auto task = std::make_shared<std::packaged_task<ReturnType()>>(
                std::bind(std::forward<Func>(func), std::forward<Args>(args)...)
            );

            std::future<ReturnType> result = task->get_future();

            {
                std::unique_lock<std::mutex> lock(queueMutex);

                // check for stop

                taskQueue.emplace([task]() { (*task)(); });
            }

            condition.notify_one();

            return result;
        }

    private:
        std::vector<std::thread> threads;
        std::queue<std::function<void()>> taskQueue;
        std::mutex queueMutex;
        std::condition_variable condition;
        bool stop;
    };
}