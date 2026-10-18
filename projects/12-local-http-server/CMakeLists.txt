add_executable(http_server main.cpp)
add_executable(http_test test.cpp)
add_test(NAME http_test COMMAND http_test)

if(WIN32)
    target_link_libraries(http_server PRIVATE ws2_32)
endif()
