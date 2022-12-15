#include <coroutine>
#include <iostream>

struct Coroutine {
    struct promise_type {
        Coroutine get_return_object() {
            return { .h_ = std::coroutine_handle<promise_type>::from_promise(*this) };
        }
        std::suspend_never initial_suspend() noexcept { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void unhandled_exception() {}
    };
    std::coroutine_handle<promise_type> h_;
    operator std::coroutine_handle<promise_type>() const { return h_; }
    operator std::coroutine_handle<>() const { return h_; }

};

Coroutine coro() {
    std::cout << "- Nu chisto genialno" << std::endl;
    co_await std::suspend_always{};
    std::cout << "- Mozhet potomu chto ya russkii? Eto tak neozhidanno i neochevidno" << std::endl;
    co_await std::suspend_always{};
    std::cout << "- Nu dk i poshel domoi znachit, ya to tebya otlichto ponimayu" << std::endl;
    co_await std::suspend_always{};
}

int main() {
    std::coroutine_handle<> print = coro();
    std::cout << "- Why are u write in Russian" << std::endl;
    print();
    std::cout << "- I don't understand" << std::endl;
    print();
}
