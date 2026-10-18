# To-Do List Manager

Manage tasks with persistent file storage.

## Features
- Create, list, complete, delete tasks
- Unique task IDs
- Priority levels (High/Medium/Low)
- Persistent storage (tasks.dat)
- Safe file handling

## Build & Run
```bash
cmake --build build --target todo
./build/projects/03-todo-list/todo
```

## Test
```bash
./build/projects/03-todo-list/todo_test
```

## Concepts
- File I/O with fstream
- Vector container
- Struct usage
- Data persistence
