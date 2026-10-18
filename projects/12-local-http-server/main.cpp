#include <iostream>
#include <string>
#include <sstream>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
typedef int socklen_t;
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define SOCKET int
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket close
#endif

const int PORT = 8080;
const int MAX_REQUEST = 4096;

std::string handle_request(const std::string& request) {
    std::istringstream iss(request);
    std::string method, path, version;
    iss >> method >> path >> version;
    
    std::cout << "[" << method << "] " << path << "\n";
    
    // Basic path traversal check
    if (path.find("..") != std::string::npos) {
        return "HTTP/1.0 403 Forbidden\r\nContent-Length: 0\r\n\r\n";
    }
    
    std::string response_body = 
        "<!DOCTYPE html>\n"
        "<html><head><title>Local Server</title></head>\n"
        "<body><h1>Educational HTTP Server</h1>\n"
        "<p>Request: " + method + " " + path + "</p>\n"
        "<p><strong>Note:</strong> Educational only, not production-ready</p>\n"
        "</body></html>\n";
    
    std::ostringstream response;
    response << "HTTP/1.0 200 OK\r\n"
             << "Content-Type: text/html\r\n"
             << "Content-Length: " << response_body.length() << "\r\n"
             << "Connection: close\r\n"
             << "\r\n"
             << response_body;
    
    return response.str();
}

int main() {
#ifdef _WIN32
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        std::cerr << "WSAStartup failed\n";
        return 1;
    }
#endif

    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed\n";
#ifdef _WIN32
        WSACleanup();
#endif
        return 1;
    }
    
    int opt = 1;
#ifdef _WIN32
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof(opt));
#else
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
#endif
    
    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Localhost only
    server_addr.sin_port = htons(PORT);
    
    if (bind(server_socket, (sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed. Port " << PORT << " may be in use.\n";
        closesocket(server_socket);
#ifdef _WIN32
        WSACleanup();
#endif
        return 1;
    }
    
    if (listen(server_socket, 5) == SOCKET_ERROR) {
        std::cerr << "Listen failed\n";
        closesocket(server_socket);
#ifdef _WIN32
        WSACleanup();
#endif
        return 1;
    }
    
    std::cout << "=== Educational HTTP Server ===\n";
    std::cout << "Listening on http://127.0.0.1:" << PORT << "\n";
    std::cout << "Press Ctrl+C to stop\n\n";
    
    while (true) {
        sockaddr_in client_addr{};
        socklen_t client_len = sizeof(client_addr);
        SOCKET client_socket = accept(server_socket, (sockaddr*)&client_addr, &client_len);
        
        if (client_socket == INVALID_SOCKET) continue;
        
        char buffer[MAX_REQUEST] = {0};
        int bytes_received = recv(client_socket, buffer, MAX_REQUEST - 1, 0);
        
        if (bytes_received > 0) {
            std::string request(buffer, bytes_received);
            std::string response = handle_request(request);
            send(client_socket, response.c_str(), response.length(), 0);
        }
        
        closesocket(client_socket);
    }
    
    closesocket(server_socket);
#ifdef _WIN32
    WSACleanup();
#endif
    
    return 0;
}
