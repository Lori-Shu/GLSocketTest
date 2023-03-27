#pragma once
#define LinuxVersion
#ifdef WindowsVersion
#include<winsock2.h>
#endif
#ifdef LinuxVersion
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#endif


#include <array>
#include <string>
namespace mystd{
    class GLSocketClient{
        public:
         GLSocketClient();
        ~GLSocketClient();
        
        void sendStr2Server();
        void receiveStrFromServer();
        void loopCmd();

       private:
        void connectServer();
        void initWindowsWSA();
        void freeWindowsWSA();
        std::array<char, 1024> clientCharBuffer;
        int32_t client;
    };
}