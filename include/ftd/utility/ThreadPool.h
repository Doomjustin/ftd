#ifndef FTD_UTILITY_THREAD_POOL_H
#define FTD_UTILITY_THREAD_POOL_H

#include "FunctionWrapper.h"

#include <thread>
#include <future>
#include <functional>
#include <utility>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <vector>

namespace ftd {

class ThreadPool {
public:
    ThreadPool();
    explicit ThreadPool(int max_threads);

    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    ThreadPool(ThreadPool&& other) noexcept;
    ThreadPool& operator=(ThreadPool&& other) noexcept;

    ~ThreadPool();

    template<typename F, typename... Args>
        requires std::invocable<F, Args...>
    std::future<std::invoke_result_t<F, Args...>> submit(F f, Args&&... args)
    {
        using result_type = std::invoke_result_t<F, Args...>;

        std::packaged_task<result_type()> task{ std::bind(std::move(f), std::forward<Args>(args)...) };
        auto res = task.get_future();

        {
            std::unique_lock<std::mutex> lock{ m_ };
            tasks_.emplace(std::move(task));
            cv_.notify_one();
        }

        return res;
    }

    constexpr bool stopped() const noexcept { return !done_; }
    bool completed() const noexcept { return tasks_.empty(); }

    void stop();

    void restart();

private:
    static constexpr int max_threads_ = 16;

    bool done_;
    std::mutex m_;
    std::condition_variable cv_;
    std::vector<std::thread> threads_;
    std::queue<FunctionWrapper> tasks_;

    void thread_work();
};

} // namespace ftd

#endif // FTD_UTILITY_THREAD_POOL_H