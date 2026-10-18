add_executable(calculator main.cpp)
add_executable(calculator_test test.cpp)
add_test(NAME calculator_test COMMAND calculator_test)
