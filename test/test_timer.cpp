#include <ftd/utility/Timer.h>
#include <ftd/utility/Log.h>

#include <cstdlib>


void test(int i)
{
    ftd::log::info("i = {}", i);
}

void once_task()
{
    ftd::log::info("this is an one time task");
}

struct A {
    void test_member(int x)
    {
        ftd::log::info("this is a class task, {}", x);
    }
};


int main()
{
    A a{};
    ftd::TimerManager timer_manager{};

    using namespace std::chrono_literals;
    timer_manager.add_timer(5s, 2s, test, 1);
    timer_manager.add_timer(1s, once_task);
    timer_manager.add_timer(2s, 2s, &A::test_member, a, 1);

    timer_manager.run();

    return EXIT_SUCCESS;
}