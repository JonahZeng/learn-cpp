#include <iostream>
#include <thread>
#include <functional>
#include <vector>
#include <shared_mutex> //c++ 17

static std::shared_mutex mut;
static std::vector<int> a{};

void f(std::vector<int> &in)
{
    std::unique_lock lck{mut};
    for (int i=0; i<20; ++i)
    {
        a.push_back(i);
    }
}

class F
{
private:
    std::vector<int>* data;
public:
    explicit F(std::vector<int>* in) : data(in) {}
    void operator()()
    {
        std::shared_lock lck{mut};
        for (auto &x : *data)
        { 
            std::cout << x << ", ";
        }
        std::cout << std::endl;
    }
};

void g(std::vector<int>* in)
{
    std::shared_lock lck{mut};
    for (auto &x : *in)
    { 
        std::cout << x << ", ";
    }
    std::cout << std::endl;
}

int main()
{
    std::thread t1{f, ref(a)};
    std::thread t2{F(&a)};
    std::thread t3{ []() { g(&a); }};

    t1.join();
    t2.join();
    t3.join();
    return 0;
}