add_executable(tictactoe main.cpp)
add_executable(tictactoe_test test.cpp)
add_test(NAME tictactoe_test COMMAND tictactoe_test)
