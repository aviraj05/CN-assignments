#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    // 1. Create client socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Socket creation error\n";
        return 1;
    }

    // 2. Setup server address struct
    sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    // 3. Connect to server
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection Failed\n";
        return 1;
    }

    // 4. Take user input for calculation
    std::string num1, op, num2;
    std::cout << "Enter first number: ";
    std::cin >> num1;
    std::cout << "Enter operator (+, -, *, /): ";
    std::cin >> op;
    std::cout << "Enter second number: ";
    std::cin >> num2;

    // 5. Pack inputs into a single string message
    std::string message = num1 + " " + op + " " + num2;
    send(sock, message.c_str(), message.length(), 0);

    // 6. Receive calculated result from server
    char buffer[1024] = {0};
    read(sock, buffer, 1024);
    std::cout << "Result from Server: " << buffer << "\n";

    // 7. Close socket
    close(sock);
    return 0;
}