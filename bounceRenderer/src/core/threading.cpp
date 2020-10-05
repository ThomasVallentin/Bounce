//
// Created by Thomas Vallentin on 30/08/2020.
//

#include "core/threading.hpp"

void ThreadPool::start() {
    for (size_t i=0; i < threadCount ; i++) {
        threads.emplace_back(std::bind(&ThreadPool::threadLoop, this));
    }
}

void ThreadPool::join() {
    joining = true;
    condition.notify_all();
    for (auto& thread : threads)
        thread.join();

    threads.clear();
}

void ThreadPool::stop() {
    stopping = true;
    condition.notify_all();
    for (auto& thread : threads)
        thread.join();

    threads.clear();
}

void ThreadPool::addJob(const std::function<void()> &job) {
    std::unique_lock<std::mutex> lock(queueMutex);

    jobs.push(job);

    condition.notify_one();
}

void ThreadPool::threadLoop() {
    while (true) {
        std::function<void()> job;
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            condition.wait(lock, [&] { return joining || stopping || !jobs.empty(); });

            if ((joining && jobs.empty()) || stopping)
                return;

            job = jobs.front();
            jobs.pop();
        }
        job();
    }
}
