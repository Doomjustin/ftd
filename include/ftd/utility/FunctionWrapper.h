#ifndef FTD_UTILITY_FUNCTION_WRAPPER_H
#define FTD_UTILITY_FUNCTION_WRAPPER_H

#include <memory>
#include <utility>

namespace ftd {

class FunctionWrapper {
public:
    FunctionWrapper()
      : callable_{ nullptr }
    {}

    // copy func
    template<typename F>
    explicit FunctionWrapper(F f)
      : callable_{ std::make_unique<Functor<F>>(std::move(f)) }
    {}

    FunctionWrapper(const FunctionWrapper&) = delete;
    FunctionWrapper& operator=(const FunctionWrapper&) = delete;

    FunctionWrapper(FunctionWrapper&&) noexcept = default;
    FunctionWrapper& operator=(FunctionWrapper&&) noexcept = default;

    ~FunctionWrapper() = default;

    void operator()() noexcept
    {
        callable_->call();
    }

    explicit operator bool() const noexcept { return static_cast<bool>(callable_); }

private:
    struct Callable {
    public:
        virtual ~Callable() = default;

        virtual void call() noexcept = 0;
    };

    template<typename F>
    struct Functor: public Callable {
        F f;

        explicit Functor(F&& func)
          : f{ std::forward<F>(func) }
        {}

        void call() noexcept override
        {
            f();
        }

    };

    std::unique_ptr<Callable> callable_;
};

} // namespace ftd

#endif // FTD_UTILITY_FUNCTION_WRAPPER_H