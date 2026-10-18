add_executable(todo main.cpp)
add_executable(todo_test test.cpp)
add_test(NAME todo_test COMMAND todo_test)
