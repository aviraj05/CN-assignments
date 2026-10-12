#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    // 1. Create socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Socket creation error\n";
        return 1;
    }

    // 2. Define server address
    sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    // 3. Connect to server
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection Failed\n";
        return 1;
    }

    // 4. Send message
    const char* message = "Hello Server";
    send(sock, message, strlen(message), 0);

    // 5. Receive response
    char buffer[1024] = {0};
    read(sock, buffer, 1024);
    std::cout << "Server: " << buffer << "\n";

    // 6. Close socket
    close(sock);
    return 0;
}