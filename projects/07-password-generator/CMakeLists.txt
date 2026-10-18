add_executable(passgen main.cpp)
add_executable(passgen_test test.cpp)
add_test(NAME passgen_test COMMAND passgen_test)
