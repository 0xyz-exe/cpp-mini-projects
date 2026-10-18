# Multithreaded Task Queue

Thread-safe task queue with worker pool.

## Features
- Thread-safe submission
- Worker thread pool
- Mutex + condition variable synchronization
- Graceful shutdown
- Exception handling

## Build & Run
```bash
cmake --build build --target task_queue
./build/projects/14-task-queue/task_queue
```

## Test
```bash
./build/projects/14-task-queue/queue_test
```

## Concepts
- std::thread
- std::mutex, std::condition_variable
- RAII for thread management
- std::atomic
- Lambda captures
- Move semantics
