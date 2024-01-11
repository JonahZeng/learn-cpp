# learn-cpp
---
personal c plus plus note

## chapter1-thread
使用cpp-std-17标准，测试thread创建，join，不使用同步技术的情况下，乱序输出；
```bat
PS E:\learn-cpp\chapter1-thread\bin\Debug> ."E:/learn-cpp/chapter1-thread/bin/Debug/chapter1-thread.exe"
0, 1, 2, 3, 4, 5, 0,
1, 2, 3, 4, 5,
PS E:\learn-cpp\chapter1-thread\bin\Debug> ."E:/learn-cpp/chapter1-thread/bin/Debug/chapter1-thread.exe"
00, 1, 2, 3, 4, 5,
, 1, 2, 3, 4, 5,
```
同时演示了：
- 使用函数以及参数构造thread对象
- 使用重载了`()`操作符的对象构造thread对象

## chapter2-thread
- 演示如何获取thread的计算结果
- 如何在thread间使用共享数据，`std::scoped_lock<std::mutex>::scoped_lock(mutex)`
- scoped_lock同时获取多个锁

## chapter3-thread
- shared_mutex，unique_mutex的使用
```bat
PS E:\learn-cpp\chapter3-thread\bin\Debug> ."E:/learn-cpp/chapter3-thread/bin/Debug/chapter3-thread.exe"
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 0, 1, 2, 3, 4, 14, 5, 6, 7, 8, 9, 1015, 16, 17, 18, 19, , 11, 
12, 13, 14, 15, 16, 17, 18, 19, 
PS E:\learn-cpp\chapter3-thread\bin\Debug> ."E:/learn-cpp/chapter3-thread/bin/Debug/chapter3-thread.exe"
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 
10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 
PS E:\learn-cpp\chapter3-thread\bin\Debug> ."E:/learn-cpp/chapter3-thread/bin/Debug/chapter3-thread.exe"
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 
PS E:\learn-cpp\chapter3-thread\bin\Debug> 
```

```cpp
//thread0
std::unique_lock lck{mut}; //写入线程，独占锁
for (int i=0; i<20; ++i)
{
    a.push_back(i);
}

//thread1
std::shared_lock lck{mut}; //读取线程，共享锁
for (auto &x : *data)
{ 
    std::cout << x << ", ";
}
std::cout << std::endl;

//thread2
std::shared_lock lck{mut}; //读取线程，共享锁
for (auto &x : *in)
{ 
    std::cout << x << ", ";
}
std::cout << std::endl;
```

## chapter4-thread
演示原子量atomic的使用。
原子量相比锁更轻量，对于一个简单的共享变量读写竞争，使用原子量更快；

```cpp
std::atomic<int> acnt;
int cnt;

void f()
{
    for (int n = 0; n < 10000; ++n)
    {
        ++acnt;
        ++cnt;
        // 注意: 对于此示例，宽松内存定序已经足够，
        // 例如 acnt.fetch_add(1, std::memory_order_relaxed);
    }
}
 
int main()
{
    {
        std::vector<std::thread> pool;
        for (int n = 0; n < 10; ++n) //10个线程同时操作acnt cnt，每个线程累加10000次
            pool.emplace_back(f);
        
        for(std::thread& th: pool)
        {
            th.join();
        }
    }
 
    std::cout << "原子计数器为 " << acnt << '\n'
              << "非原子计数器为 " << cnt << '\n'; //非原子量因为cpu之间store buffer不同步，会导致结果错误
}
```

## chapter5-thread
演示condition_variable等待事件的使用；
当一个thread必须等待另一个thread完成某个工作以后才能继续往下进行的时候，使用condition_variable是比较合适的；