#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 10);

    std::cout << "Backend started on port 8080..." << std::endl;

    while (true) {
        int new_socket = accept(server_fd, NULL, NULL);
        if (new_socket < 0) continue;

        // Proper HTTP response format
        std::string hostname = getenv("HOSTNAME") ? getenv("HOSTNAME") : "unknown";
        std::string body = "Served by backend: " + hostname + "\n";
        std::string response = 
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: " + std::to_stdio(body.length()) + "\r\n"
            "Connection: close\r\n"
            "\r\n" + body;

        send(new_socket, response.c_str(), response.length(), 0);
        close(new_socket);
    }
    return 0;
}