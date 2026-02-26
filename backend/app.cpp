#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080); // Matches your Nginx config

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    std::cout << "Backend started on port 8080..." << std::endl;

    while (true) {
        int new_socket = accept(server_fd, NULL, NULL);
        std::string response = "HTTP/1.1 200 OK\nContent-Type: text/plain\n\nServed by backend: ";
        response += getenv("HOSTNAME");
        response += "\n";
        send(new_socket, response.c_str(), response.length(), 0);
        close(new_socket);
    }
    return 0;
}