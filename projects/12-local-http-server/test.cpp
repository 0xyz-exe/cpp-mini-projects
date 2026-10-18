#include <cassert>
#include <iostream>
#include <string>
#include <sstream>

std::string parse_request_path(const std::string& request) {
    std::istringstream iss(request);
    std::string method, path, version;
    iss >> method >> path >> version;
    return path;
}

int main() {
    std::string request = "GET /index.html HTTP/1.1\r\nHost: localhost\r\n\r\n";
    std::string path = parse_request_path(request);
    assert(path == "/index.html");
    
    std::string request2 = "POST /api/data HTTP/1.0\r\n\r\n";
    std::string path2 = parse_request_path(request2);
    assert(path2 == "/api/data");
    
    std::cout << "All HTTP server tests passed\n";
    return 0;
}
