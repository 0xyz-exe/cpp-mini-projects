add_executable(library main.cpp)
add_executable(library_test test.cpp)
add_test(NAME library_test COMMAND library_test)
