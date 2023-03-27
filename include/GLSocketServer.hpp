#pragma once
#define LinuxVersion
#ifdef WindowsVersion
#include <winsock2.h>
#endif
#ifdef LinuxVersion
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#endif


#include <array>
#include <string>
#include <unordered_map>
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
     #ifdef WindowsVersion
     WSADATA wsaData;
     #endif
     int32_t serverSocket;
     std::unordered_map<std::string, int32_t> clientMap;
     std::array<char, 1024> charBuffer;
};
}