#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <algorithm>
#include <cctype>

#define PORT 8080
#define BUFFER_SIZE 1024


std::string toLower(const std::string &str)
{
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return lowerStr;
}

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: ./client <server_ip>" << std::endl;
        return 1;
    }

    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};

    int sock = 0;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cerr << "Socket creation error" << std::endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0)
    {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        return -1;
    }

    if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cerr << "Connection Failed" << std::endl;
        return -1;
    }


    std::string currentDirectory = "/home/byaketava/CLionProjects/lab8/Server/ServerFolder/";
    while (true)
    {
        std::string message;
        while (true)
        {
            std::cout << currentDirectory << "> ";
            std::getline(std::cin, message);

            std::string lowercaseMessage = toLower(message);

            if (lowercaseMessage == "quit" || lowercaseMessage == "exit")
            {
                send(sock, "quit", 4, 0);
                std::cout << "Exiting..." << std::endl;
                exit(1);
            } else if (lowercaseMessage == "cd")
            {
                std::cout << "Usage: cd <directory_name>" << std::endl;
            } else if (lowercaseMessage == "list")
            {
                send(sock, "list", 4, 0);
                break;
            } else if (lowercaseMessage == "info")
            {
                send(sock, "info", 4, 0);
                break;
            } else if (lowercaseMessage.find("cd ") == 0)
            {
                send(sock, message.c_str(), message.length(), 0);
                break;
            } else if (lowercaseMessage.find("echo ") == 0)
            {
                send(sock, message.c_str(), message.length(), 0);
                break;
            } else
            {
                std::cout << "Invalid command" << std::endl;
            }
        }
        int valread = read(sock, buffer, BUFFER_SIZE);
        std::cout << "Response: \n" << buffer << std::endl;

        if (strncmp(message.c_str(), "cd", 2) == 0 && valread > 0)
        {
            std::string response(buffer);
            size_t pos = response.find("Changed directory to: ");
            if (pos != std::string::npos)
            {
                currentDirectory = response.substr(pos + strlen("Changed directory to: "));
            }
        }
        memset(buffer, 0, BUFFER_SIZE);
    }
    return 0;
}
