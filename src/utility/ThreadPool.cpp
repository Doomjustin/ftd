#include "utility/ThreadPool.h"

namespace ftd {

ThreadPool::ThreadPool()
  : ThreadPool{ max_threads_ }
{}

ThreadPool::ThreadPool(int max_threads)
  : done_{ true }
{
    for (auto i = 0; i < max_threads; ++i) {
        std::thread t{ &ThreadPool::thread_work, this };
        threads_.emplace_back(std::move(t));
    }
}

ThreadPool::ThreadPool(ThreadPool&& other) noexcept
{
    std::lock(m_, other.m_);
    done_ = other.done_;
    threads_ = std::move(other.threads_);
    tasks_ = std::move(other.tasks_);
}

ThreadPool& ThreadPool::operator=(ThreadPool&& other) noexcept
{
    std::lock(m_, other.m_);
    std::swap(done_, other.done_);
    std::swap(threads_, other.threads_);
    std::swap(tasks_, other.tasks_);

    return *this;
}

ThreadPool::~ThreadPool()
{
    stop();
}

void ThreadPool::stop()
{
    {
        std::unique_lock<std::mutex> lock{ m_ };
        if (!done_) return;

        done_ = false;
        cv_.notify_all();
    }

    for (auto&& t: threads_)
        if (t.joinable())
            t.join();
}

void ThreadPool::restart()
{
    if (!done_) {
        done_ = true;

        for (auto&& t: threads_)
            t = std::thread{ &ThreadPool::thread_work, this };
    }
}

void ThreadPool::thread_work()
{
    FunctionWrapper task;
    while (done_) {
        {
            std::unique_lock<std::mutex> lock{ m_ };
            cv_.wait(lock, [this] () { return !tasks_.empty() || !done_; });
            if (!done_) continue;

            task = std::move(tasks_.front());
            tasks_.pop();
        }

        task();
    }
}

} // namespace ftd