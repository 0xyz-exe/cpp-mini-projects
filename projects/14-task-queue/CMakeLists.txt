add_executable(task_queue main.cpp)
add_executable(queue_test test.cpp)
add_test(NAME queue_test COMMAND queue_test)

if(NOT WIN32)
    find_package(Threads REQUIRED)
    target_link_libraries(task_queue PRIVATE Threads::Threads)
    target_link_libraries(queue_test PRIVATE Threads::Threads)
endif()
