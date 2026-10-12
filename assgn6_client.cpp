#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        std::cerr << "Socket creation error\n";
        return 1;
    }

    sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    // Get initial message from user
    std::string message;
    std::cout << "Enter your message: ";
    std::getline(std::cin, message);

    socklen_t serv_len = sizeof(serv_addr);
    sendto(sock, message.c_str(), message.length(), 0, (struct sockaddr*)&serv_addr, serv_len);

    // Interactive menu loop on client side
    while (true) {
        std::cout << "\n1. Reverse the message\n";
        std::cout << "2. Change case of the message\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter choice: ";
        
        std::string choice;
        if (!(std::cin >> choice)) break;

        // Send choice to server
        sendto(sock, choice.c_str(), choice.length(), 0, (struct sockaddr*)&serv_addr, serv_len);

        // Receive response from server
        char buffer[1024] = {0};
        ssize_t n = recvfrom(sock, buffer, 1024, 0, (struct sockaddr*)&serv_addr, &serv_len);
        if (n < 0) break;

        std::string result(buffer, n);
        if (result == "EXIT") {
            std::cout << "Server closed the connection.\n";
            break;
        }
        
        std::cout << "Server: " << result << "\n";
    }

    close(sock);
    return 0;
}