#pragma once
#define LinuxVersion
#ifdef WindowsVersion
#include <winsock2.h>
#endif
#ifdef LinuxVersion
#include<sys/socket.h>
#endif
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include <array>
#include <cstdint>
#include <iostream>

namespace mystd{
class GGLSelectMultiIO final{
    public:
     static constexpr int32_t PORT = 8975;
     GGLSelectMultiIO();
     ~GGLSelectMultiIO();
    private:
     void createServerSocket();
     void initWindowsWSA();
     void freeWindowsWSA();
     void runSelectMainLoop();
     void handleMsg(int32_t socketFD);
     void closeSockets();
     int32_t maxFd;
    //  select函数会把所有的描述符按照类型标记各个set
     fd_set readSet, writeSet, exceptionSet,allSet;
     #ifdef WindowsVersion
     WSADATA wsaData;
     #endif
     int32_t serverSocket;
     std::array<char,1024> msgBuffer;
};
}