#pragma once
#include <winsock2.h>

#include <string>
#include <unordered_map>
#include<array>
    namespace mystd {
class GLSocketServer {
    public:
     GLSocketServer(std::string port);
     ~GLSocketServer();
     
     void acceptClient();
     void receiveFromClient();
     void printAllClientNames();
     void sendStr2Client();
     void loopCmd();

    private:
     void bindPortAndListen(std::string port);
     void initWindowsWSA();
     void freeWindowsWSA();
     void freeClients();
     uint32_t acceptConnectionQueueLength = 20;
     WSADATA wsaData;
     SOCKET serverSocket{};
     std::unordered_map<std::string, SOCKET> clientMap;
     std::array<char, 1024> charBuffer;
};
}