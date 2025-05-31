#include <iostream>
#include <fstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <pthread.h>
#include <sys/stat.h>
#include <dirent.h>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>


#define PORT 8080
#define BUFFER_SIZE 1024

std::string rootDirectory = "/home/byaketava/CLionProjects/lab8/Server/ServerFolder/";
size_t rootPathFoldersLevel;


std::string getInfoMessage()
{
    std::ifstream infoFile("serverinfo.txt");
    std::string infoMessage;
    std::string line;
    if (infoFile.is_open())
    {
        while (getline(infoFile, line))
        {
            infoMessage += line + "\n";
        }
        infoFile.close();
    } else
    {
        infoMessage = "Server info file not found.";
    }
    return infoMessage;
}

std::string getObjectType(const std::string &path)
{
    struct stat path_stat;
    stat(path.c_str(), &path_stat);
    if (S_ISREG(path_stat.st_mode))
    {
        return "file";
    } else if (S_ISDIR(path_stat.st_mode))
    {
        return "directory";
    } else
    {
        return "unknown";
    }
}

std::string getListMessage(const std::string &currentDirectory)
{
    std::string listMessage;
    DIR *dir;
    struct dirent *ent;
    std::cout << "[" << currentDirectory << "]\n";
    if ((dir = opendir(currentDirectory.c_str())) != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            std::string itemName = ent->d_name;
            std::string itemType = getObjectType(currentDirectory + "/" + itemName);
            if (itemType == "file")
            {
                listMessage += "\033[34m";
            } else if (itemType == "directory")
            {
                listMessage += "\033[33m";
            }
            listMessage += itemName;
            listMessage += "\033[0m";
            listMessage += "\n";
        }
        closedir(dir);
    } else
    {
        perror("Unable to open directory");
        listMessage = "Unable to open directory.";
    }
    return listMessage;
}


bool directoryExists(const std::string &path)
{
    struct stat info;
    if (stat(path.c_str(), &info) != 0)
    {
        return false;
    }
    return (info.st_mode & S_IFDIR) != 0;
}


std::vector<std::string> split(const std::string &s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

std::string changeDirectory(const std::string &command, const std::string &currentDirectory)
{
    std::string fullPath = command;
    std::vector<std::string> directories = split(fullPath, '/');

    if ((command[0] == '.' && command[1] == '/') || command[0] == '/')
    {
        if (command.size() < 3)
        {
            return currentDirectory;
        }
        directories.erase(directories.begin());
        size_t first = command.find_first_not_of("./ ");
        size_t last = command.find_last_not_of("./ ");
        fullPath = rootDirectory + command.substr(first, last - first + 1);
        if (directoryExists(fullPath))
        {
            return fullPath + "/";
        } else
        {
            return currentDirectory;
        }
    }

    std::vector<std::string> currentPath = split(currentDirectory, '/');

    for (const auto &directory: directories)
    {
        if (directory == "..")
        {
            if (currentPath.size() > rootPathFoldersLevel)
            {
                currentPath.pop_back();
            } else
            {
                return currentDirectory;
            }
        } else if (directory != "." && directory != "")
        {
            currentPath.push_back(directory);
        }
    }

    std::string newPath = currentPath.front();
    for (size_t i = 1; i < currentPath.size(); ++i)
    {
        newPath += "/" + currentPath[i];
    }

    if (directoryExists(newPath))
    {

        return newPath;
    }

    return currentDirectory;
}


void *connection_handler(void *socket_desc)
{
    int new_socket = *(int *) socket_desc;
    char buffer[BUFFER_SIZE] = {0};
    int valread;
    std::string currentDirectory = rootDirectory;

    while ((valread = read(new_socket, buffer, BUFFER_SIZE)) > 0)
    {
        if (strncmp(buffer, "info", 4) == 0)
        {
            std::string infoMessage = getInfoMessage();
            send(new_socket, infoMessage.c_str(), infoMessage.length(), 0);
            printf("Info message sent\n");

        } else if (strncmp(buffer, "list", 4) == 0)
        {
            std::string listMessage = getListMessage(currentDirectory);
            send(new_socket, listMessage.c_str(), listMessage.length(), 0);
            printf("List message sent\n");

        } else if (strncmp(buffer, "cd", 2) == 0)
        {
            std::string newDir = buffer + 3;
            newDir = newDir.substr(0, newDir.find('\n'));
            currentDirectory = changeDirectory(newDir, currentDirectory);
            std::string msg = "Changed directory to: " + currentDirectory;
            send(new_socket, msg.c_str(), msg.length(), 0);
            printf("Changed directory\n");

        } else if (strncmp(buffer, "echo", 4) == 0)
        {
            send(new_socket, buffer, strlen(buffer), 0);
            printf("Echo message sent\n");

        } else
        {
            std::string unkonwnmsg = "Unknown command";
            send(new_socket, unkonwnmsg.c_str(), unkonwnmsg.length(), 0);
            printf("Unknown command\n");
        }
        memset(buffer, 0, BUFFER_SIZE);
    }

    if (valread == 0)
    {
        printf("Client disconnected\n");
    } else
    {
        perror("recv failed");
    }

    close(new_socket);
    free(socket_desc);
    pthread_exit(NULL);
}

int main()
{
    std::vector<std::string> rootPath = split(rootDirectory, '/');
    rootPathFoldersLevel = rootPath.size();

    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (true)
    {
        if ((new_socket = accept(server_fd, (struct sockaddr *) &address, (socklen_t *) &addrlen)) < 0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        pthread_t sniffer_thread;
        int *new_sock = (int *) malloc(1);
        *new_sock = new_socket;

        if (pthread_create(&sniffer_thread, NULL, connection_handler, (void *) new_sock) < 0)
        {
            perror("could not create thread");
            return 1;
        }
        printf("Handler assigned\n");
    }
    return 0;
}
