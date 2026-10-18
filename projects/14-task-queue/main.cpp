#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include <vector>
#include <atomic>
#include <chrono>

class TaskQueue {
    std::queue<std::function<void()>> tasks;
    std::mutex mtx;
    std::condition_variable cv;
    std::vector<std::thread> workers;
    std::atomic<bool> stop_flag{false};
    std::atomic<int> active_tasks{0};
    
public:
    TaskQueue(int num_workers) {
        for (int i = 0; i < num_workers; i++) {
            workers.emplace_back([this, i]() {
                std::cout << "Worker " << i << " started\n";
                while (true) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(mtx);
                        cv.wait(lock, [this]() { return stop_flag || !tasks.empty(); });
                        
                        if (stop_flag && tasks.empty()) {
                            std::cout << "Worker " << i << " stopping\n";
                            return;
                        }
                        
                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    
                    active_tasks++;
                    try {
                        task();
                    } catch (const std::exception& e) {
                        std::cerr << "Task exception: " << e.what() << "\n";
                    }
                    active_tasks--;
                }
            });
        }
    }
    
    void enqueue(std::function<void()> task) {
        {
            std::unique_lock<std::mutex> lock(mtx);
            if (stop_flag) {
                std::cout << "Queue is shutting down, task rejected\n";
                return;
            }
            tasks.push(std::move(task));
        }
        cv.notify_one();
    }
    
    int pending_tasks() {
        std::unique_lock<std::mutex> lock(mtx);
        return tasks.size();
    }
    
    int get_active_tasks() const {
        return active_tasks;
    }
    
    ~TaskQueue() {
        std::cout << "Shutting down task queue...\n";
        {
            std::unique_lock<std::mutex> lock(mtx);
            stop_flag = true;
        }
        cv.notify_all();
        
        for (auto& worker : workers) {
            if (worker.joinable()) worker.join();
        }
        std::cout << "All workers stopped\n";
    }
};

int main() {
    std::cout << "=== Multithreaded Task Queue ===\n\n";
    
    int num_workers = 4;
    int num_tasks = 20;
    
    std::cout << "Creating queue with " << num_workers << " workers\n";
    std::cout << "Submitting " << num_tasks << " tasks\n\n";
    
    std::atomic<int> completed{0};
    
    {
        TaskQueue queue(num_workers);
        
        for (int i = 0; i < num_tasks; i++) {
            queue.enqueue([i, &completed]() {
                std::cout << "Task " << i << " executing on thread " 
                         << std::this_thread::get_id() << "\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                completed++;
            });
        }
        
        // Wait for tasks to complete
        while (completed < num_tasks) {
            std::cout << "Progress: " << completed << "/" << num_tasks 
                     << " (pending: " << queue.pending_tasks() 
                     << ", active: " << queue.get_active_tasks() << ")\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        
        std::cout << "\nAll tasks completed\n";
    }
    
    std::cout << "\nFinal count: " << completed << "\n";
    
    return 0;
}
