#include"GLSocketClient.hpp"
#include<iostream>
#include<array>
#include<cassert>
namespace mystd{
using namespace std;
GLSocketClient::GLSocketClient(){
  #ifdef WindowsVersion
  initWindowsWSA();
  #endif
  connectServer();
}
GLSocketClient ::~GLSocketClient(){
  #ifdef WindowsVersion
    closesocket(client);
    freeWindowsWSA();
#endif
    #ifdef LinuxVersion
    close(client);
    #endif
    
}
void GLSocketClient:: connectServer(){
    // 创建套接字
    client = socket(PF_INET, SOCK_STREAM, 0);

    // 向服务器发起请求
    cout << "请输入服务器ip：";
    cin.getline(clientCharBuffer.data(), clientCharBuffer.size());
    string ipStr = clientCharBuffer.data();
    cout << "请输入服务端口：";
    cin.getline(clientCharBuffer.data(), clientCharBuffer.size());
    string port = clientCharBuffer.data();
    sockaddr_in sockAddr{};
    // memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.s_addr = inet_addr(ipStr.c_str());
    sockAddr.sin_port = htons(atoi(port.c_str()));
    cout << "连接服务中......请稍候" << endl;
    int32_t res= connect(client, (sockaddr *)&sockAddr, sizeof(sockAddr));
    assert(res == 0 && "连接服务器失败！");
    cout << "连接服务成功！" << endl;
}
void GLSocketClient::sendStr2Server(){
    cout << "请输入要发送的消息：";
    cin.getline(clientCharBuffer.data(), clientCharBuffer.size());
    string msg = clientCharBuffer.data();
    cout << "发送信息======请稍候" << msg << endl;
    int32_t res= send(client, msg.c_str(), msg.size() * sizeof(char), 0);
    
    assert(res>0&& "发送信息失败！");
    cout << "发送信息成功！" << endl;
}
void GLSocketClient::receiveStrFromServer(){
    int32_t recvSize =
        recv(client, clientCharBuffer.data(), clientCharBuffer.size() * sizeof(char), 0);
    assert(recvSize != -1 && "接收消息失败！");
    string msg = clientCharBuffer.data();
    cout << "接收到消息:" << endl;
    cout << msg;
}

void GLSocketClient::loopCmd(){
    for (;;){ try {
        cout << "请输入指令{（指令-操作）=====1-发送消息，2-接收消息}" << endl;
        cin.getline(clientCharBuffer.data(), clientCharBuffer.size());
        switch (clientCharBuffer[0]) {
          case '1':
            sendStr2Server();
            break;
          case '2':
            receiveStrFromServer();
            break;
          default:
          cout << "请输入合法的指令！" << endl;
          break;
    }
      } catch (exception e) {
    cout << e.what()<<endl;
      }
    }
}

void GLSocketClient::initWindowsWSA(){
#ifdef WindowsVersion
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
}
void GLSocketClient::freeWindowsWSA(){
#ifdef WindowsVersion
    // 终止 DLL 的使用
    WSACleanup();
    #endif
}

}