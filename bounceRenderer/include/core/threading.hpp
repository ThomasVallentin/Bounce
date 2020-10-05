//
// Created by Thomas Vallentin on 30/08/2020.
//

#ifndef BOUNCE_THREADING_HPP
#define BOUNCE_THREADING_HPP

#include <iostream>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <queue>


class ThreadPool{
public:
    ThreadPool() : threadCount(std::thread::hardware_concurrency()) {}
    explicit ThreadPool(const unsigned int&threadCount) : threadCount(threadCount){}

    void start();
    void join();
    void stop();

    void addJob(const std::function<void()>& job);
    void threadLoop();

    unsigned int threadCount;
    std::queue<std::function<void()>> jobs;

private:
    std::vector<std::thread> threads;

    std::mutex queueMutex;
    std::condition_variable condition;

    bool stopping = false;
    bool joining = false;
};

#endif //BOUNCE_THREADING_HPP
