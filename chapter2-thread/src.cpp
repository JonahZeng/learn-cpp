#include <iostream>
#include <thread>
#include <functional>
#include <vector>
#include <mutex>

static std::mutex mut;
static int totalSum = 0;

static std::mutex mutTimes;
static int totalTimes = 0;

void f(std::vector<int> &in, int* out)
{
    for (auto &x : in)
    {
        *out += x;
        std::scoped_lock lck{mut, mutTimes};
        totalSum += x;
        totalTimes += 1;
    }
}

class F
{
private:
    std::vector<int> data;
    int* data_out;
public:
    F(std::vector<int> &in, int* out) : data(in), data_out(out) {}
    void operator()()
    {
        for (auto &x : data)
        {
            *data_out += x;
            std::scoped_lock lck{mut, mutTimes};
            totalSum += x;
            totalTimes += 1;
        }
    }
};

int g(std::vector<int>& in)
{
    int res = 0;
    for(auto& x : in)
    {    
        res += x;
        std::scoped_lock lck{mut, mutTimes};
        totalSum += x;
        totalTimes += 1;
    }
    return res;
}

int main()
{
    int res1 = 0;
    int res2 = 0;
    int res3 = 0;

    std::vector<int> a{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    std::thread t1{f, ref(a), &res1};
    std::thread t2{F(a, &res2)};
    std::thread t3{ [&]() {res3 = g(a);}};

    t1.join();
    t2.join();
    t3.join();

    std::cout << res1 << ", " << res2 << ", " << res3 << std::endl;

    std::cout << totalSum  << ", " << totalTimes << std::endl;
    return 0;
}