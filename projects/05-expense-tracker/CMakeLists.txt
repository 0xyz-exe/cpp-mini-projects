add_executable(expense_tracker main.cpp)
add_executable(expense_test test.cpp)
add_test(NAME expense_test COMMAND expense_test)
