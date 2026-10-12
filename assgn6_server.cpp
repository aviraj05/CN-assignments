#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <algorithm>
#include <cctype>

int main() {
    int server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_fd < 0) {
        std::cerr << "Socket creation failed\n";
        return 1;
    }

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(5000);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "Bind failed\n";
        return 1;
    }

    std::cout << "UDP server is waiting for client...\n";

    char buffer[1024] = {0};
    sockaddr_in client_addr{};
    socklen_t client_len = sizeof(client_addr);

    // Receive initial message from client
    ssize_t n = recvfrom(server_fd, buffer, 1024, 0, (struct sockaddr*)&client_addr, &client_len);
    if (n < 0) {
        std::cerr << "recvfrom failed\n";
        close(server_fd);
        return 1;
    }

    std::string message(buffer, n);
    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
    
    std::cout << "Client connected: ('" << client_ip << "', " << ntohs(client_addr.sin_port) << ")\n";
    std::cout << "Client says: " << message << "\n";

    // Server loop listening for choice commands from client
    while (true) {
        char choice_buffer[1024] = {0};
        ssize_t cn = recvfrom(server_fd, choice_buffer, 1024, 0, (struct sockaddr*)&client_addr, &client_len);
        if (cn < 0) break;

        std::string choice(choice_buffer, cn);

        if (choice == "1") {
            std::reverse(message.begin(), message.end());
        } else if (choice == "2") {
            for (char &c : message) {
                if (std::islower(c)) c = std::toupper(c);
                else if (std::isupper(c)) c = std::tolower(c);
            }
        } else if (choice == "3") {
            std::string exit_msg = "EXIT";
            sendto(server_fd, exit_msg.c_str(), exit_msg.length(), 0, (struct sockaddr*)&client_addr, client_len);
            break;
        } else {
            // Invalid choice handling
            std::string err_msg = "Invalid choice";
            sendto(server_fd, err_msg.c_str(), err_msg.length(), 0, (struct sockaddr*)&client_addr, client_len);
            continue;
        }

        // Send updated message back to client
        sendto(server_fd, message.c_str(), message.length(), 0, (struct sockaddr*)&client_addr, client_len);
        std::cout << "Message sent to client: " << message << "\n";
    }

    close(server_fd);
    return 0;
}