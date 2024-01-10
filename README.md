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