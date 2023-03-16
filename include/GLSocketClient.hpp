#pragma once
#include<winsock2.h>
#include<string>
#include<array>
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
        SOCKET client{};
    };
}