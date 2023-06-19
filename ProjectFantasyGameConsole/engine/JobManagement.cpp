#include "JobManagement.hpp"

#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>

namespace FantasyGameEngine
{

    class ThreadPool {
    public:
        explicit ThreadPool(size_t numThreads)
            : stop(false)
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

        ~ThreadPool() {
            {
                std::unique_lock<std::mutex> lock(queueMutex);
                stop = true;
            }

            condition.notify_all();

            for (std::thread& thread : threads)
                thread.join();
        }

        template<typename Func, typename... Args>
        auto enqueue(Func&& func, Args&&... args) -> std::future<typename std::result_of<Func(Args...)>::type> {
            using ReturnType = typename std::result_of<Func(Args...)>::type;

            auto task = std::make_shared<std::packaged_task<ReturnType()>>(
                std::bind(std::forward<Func>(func), std::forward<Args>(args)...)
            );

            std::future<ReturnType> result = task->get_future();

            {
                std::unique_lock<std::mutex> lock(queueMutex);

                // Don't allow enqueueing after stopping the pool
                if (stop)
                    throw std::runtime_error("enqueue on stopped ThreadPool");

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