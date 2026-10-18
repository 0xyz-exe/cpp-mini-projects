add_executable(text_analyzer main.cpp)
add_executable(analyzer_test test.cpp)
add_test(NAME analyzer_test COMMAND analyzer_test)
