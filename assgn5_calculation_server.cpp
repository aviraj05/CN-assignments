#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sstream>

int main() {
    // 1. Create server socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        std::cerr << "Socket creation failed\n";
        return 1;
    }

    // 2. Bind address and port
    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(5000);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "Bind failed\n";
        return 1;
    }

    // 3. Listen for connection
    if (listen(server_fd, 1) < 0) {
        std::cerr << "Listen failed\n";
        return 1;
    }
    std::cout << "Server is waiting for client...\n";

    // 4. Accept client connection
    int addrlen = sizeof(address);
    int client_sock = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
    if (client_sock < 0) {
        std::cerr << "Accept failed\n";
        return 1;
    }
    std::cout << "Client connected!\n";

    // 5. Receive message string (e.g., "10 + 5")
    char buffer[1024] = {0};
    read(client_sock, buffer, 1024);
    std::string data(buffer);
    std::cout << "Client sent: " << data << "\n";

    // 6. Parse numbers and operator using stringstream
    std::stringstream ss(data);
    double num1, num2;
    char op;
    ss >> num1 >> op >> num2;

    // 7. Perform calculation
    std::string result_str;
    if (op == '+') {
        result_str = std::to_string(num1 + num2);
    } else if (op == '-') {
        result_str = std::to_string(num1 - num2);
    } else if (op == '*') {
        result_str = std::to_string(num1 * num2);
    } else if (op == '/') {
        if (num2 != 0) {
            result_str = std::to_string(num1 / num2);
        } else {
            result_str = "Error: Division by zero";
        }
    } else {
        result_str = "Error: Invalid operator";
    }

    // 8. Send result back to client
    send(client_sock, result_str.c_str(), result_str.length(), 0);

    // 9. Close sockets
    close(client_sock);
    close(server_fd);
    return 0;
}