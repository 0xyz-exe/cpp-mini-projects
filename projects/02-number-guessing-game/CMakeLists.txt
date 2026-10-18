add_executable(guessing_game main.cpp)
add_executable(guessing_test test.cpp)
add_test(NAME guessing_test COMMAND guessing_test)
