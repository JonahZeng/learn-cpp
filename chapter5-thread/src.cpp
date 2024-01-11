#include <iostream>
#include <thread>
#include <queue>
#include <condition_variable>
#include <chrono>

using namespace std::chrono;

class Message 
{
public:
    int id;
};

static std::queue<Message> mqueue;
static std::condition_variable mcond;
static std::mutex mmutex;

void consumer()
{
    while(true)
    {
        std::unique_lock lck{mmutex};
        mcond.wait(lck, [](){ return !mqueue.empty(); });

        auto m = mqueue.front();
        std::cout << "accept " << m.id << std::endl;
        mqueue.pop();
        lck.unlock();
        if(m.id > 10)
        {
            break;
        }
    }
}

void producer()
{
    int cnt = 0;
    while(true)
    {
        Message m;
        m.id = cnt;
        std::scoped_lock lck{mmutex};
        std::cout << "push " << m.id << std::endl;
        mqueue.push(m);
        mcond.notify_one();  
        cnt += 1;
        if(cnt > 11)
        {
            break;
        }
    }
}
 
int main()
{
    std::thread j1{consumer};
    std::thread j2{producer};

    j2.join();
    j1.join();

    return 0;
}