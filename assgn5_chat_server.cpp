#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    // 1. Create socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        std::cerr << "Socket creation failed\n";
        return 1;
    }

    // 2. Bind to IP and Port
    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // 127.0.0.1 equivalent
    address.sin_port = htons(5000);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "Bind failed\n";
        return 1;
    }

    // 3. Listen for connections
    if (listen(server_fd, 1) < 0) {
        std::cerr << "Listen failed\n";
        return 1;
    }
    std::cout << "Server is waiting for client...\n";

    // 4. Accept connection
    int addrlen = sizeof(address);
    int client_sock = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
    if (client_sock < 0) {
        std::cerr << "Accept failed\n";
        return 1;
    }
    std::cout << "Client connected!\n";

    // 5. Receive message
    char buffer[1024] = {0};
    read(client_sock, buffer, 1024);
    std::cout << "Client says: " << buffer << "\n";

    // 6. Send response
    const char* response = "Hello from Server";
    send(client_sock, response, strlen(response), 0);

    // 7. Close sockets
    close(client_sock);
    close(server_fd);
    return 0;
}