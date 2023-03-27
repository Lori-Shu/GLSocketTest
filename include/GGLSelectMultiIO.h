#pragma once
#include <winsock2.h>

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
     void handleMsg(SOCKET socketFD);
     void closeSockets();
     int32_t maxFd;
    //  select函数会把所有的描述符按照类型标记各个set
     fd_set readSet, writeSet, exceptionSet,allSet;
     WSADATA wsaData;
     SOCKET serverSocket;
     std::array<char,1024> msgBuffer;
};
}