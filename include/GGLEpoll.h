#pragma once
#define LinuxVersion
#ifdef LinuxVersion
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include<sys/epoll.h>
#endif
#include<iostream>
#include<array>
#include<unordered_set>

namespace mystd{
    class GGLEpoll final{
        public:
         const int32_t PORT = 8975;
         GGLEpoll();
         ~GGLEpoll();

        private:
         void createServerSocket();
         void runEpollMainLoop();
         void handleMsg(int32_t epFd, epoll_event & event);
         void closeSockets();
         static constexpr int32_t bufSize=1024;
        int32_t epollFd;
        int32_t serverSocket;

         const char * serverAddrStr="192.168.137.100";
         std::array<char, bufSize> msgBuffer;
         std::unordered_set<int32_t> clientFds;
    };
}