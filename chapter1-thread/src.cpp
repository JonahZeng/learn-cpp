#include <iostream>
#include <thread>
#include <functional>
#include <vector>

void f(std::vector<int> &in)
{
    for (auto &x : in)
        std::cout << x << ", ";
    std::cout << std::endl;
}

struct F
{
    std::vector<int> data;
    F(std::vector<int> &in) : data(in) {}
    void operator()()
    {
        for (auto &x : data)
            std::cout << x << ", ";
        std::cout << std::endl;
    }
};

int main()
{
    std::vector<int> a{0, 1, 2, 3, 4, 5};
    std::thread t1{f, ref(a)};
    std::thread t2{F(a)};

    t1.join();
    t2.join();
    return 0;
}