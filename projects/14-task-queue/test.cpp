#include <cassert>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include <vector>
#include <atomic>

class TaskQueue {
    std::queue<std::function<void()>> tasks;
    std::mutex mtx;
    std::condition_variable cv;
    std::vector<std::thread> workers;
    std::atomic<bool> stop_flag{false};
    
public:
    TaskQueue(int num_workers) {
        for (int i = 0; i < num_workers; i++) {
            workers.emplace_back([this]() {
                while (true) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(mtx);
                        cv.wait(lock, [this]() { return stop_flag || !tasks.empty(); });
                        if (stop_flag && tasks.empty()) return;
                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    task();
                }
            });
        }
    }
    
    void enqueue(std::function<void()> task) {
        {
            std::unique_lock<std::mutex> lock(mtx);
            tasks.push(std::move(task));
        }
        cv.notify_one();
    }
    
    ~TaskQueue() {
        {
            std::unique_lock<std::mutex> lock(mtx);
            stop_flag = true;
        }
        cv.notify_all();
        for (auto& worker : workers) {
            if (worker.joinable()) worker.join();
        }
    }
};

int main() {
    std::atomic<int> counter{0};
    
    {
        TaskQueue queue(2);
        
        for (int i = 0; i < 10; i++) {
            queue.enqueue([&counter]() {
                counter++;
            });
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    assert(counter == 10);
    std::cout << "All task queue tests passed\n";
    return 0;
}
