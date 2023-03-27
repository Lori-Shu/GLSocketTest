#include "GLSocketServer.hpp"

#include <array>
#include <cstdlib>
#include <exception>
#include <iostream>
#include<cassert>
namespace mystd {
using namespace std;
GLSocketServer::GLSocketServer(std::string port) {
  initWindowsWSA();
  bindPortAndListen(port);
}
void GLSocketServer::loopCmd() {
  for(;;){
    try{
    cout << " 请输入指令代号:(指令列表（代号-指令）：1-接收连接并命名，2-"
            "发送消息至指定连接，3-接收指定连接的消息,4-打印目前已建立的连接)"
         << endl;
    
    cin.getline(charBuffer.data(),2);
    switch (charBuffer[0]) {
      case '1'/* constant-expression */:
        /* code */
        acceptClient();
        break;
      case '2':
        sendStr2Client();
        break;
      case '3':
        receiveFromClient();
        break;
        case '4':
        printAllClientNames();
      default:
        cout << "请输入合规的指令" << endl;
        break;
    }
    }catch (exception e){
         cout << e.what()<< endl;
    }
  }
}
void GLSocketServer::bindPortAndListen(std::string port) {
  serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  sockaddr_in sockAddr{};
  // memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
  sockAddr.sin_family = PF_INET;                      // 使用IPv4地址
  sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // 具体的IP地址
//   cout << atoi(port.c_str());
  sockAddr.sin_port = htons(atoi(port.c_str()));  // 端口
  ::bind(serverSocket, (sockaddr *)&sockAddr, sizeof(sockaddr));
  int32_t listenRes = listen(serverSocket, 5);
  std::cout << "listen res:" << listenRes << std::endl;
}
GLSocketServer::~GLSocketServer() {
  #ifdef WindowsVersion
  closesocket(serverSocket);
  
  freeWindowsWSA();
  #endif
  #ifdef LinuxVersion
  close(serverSocket);
  #endif
  freeClients();
}
void GLSocketServer::acceptClient() {
  cout << "输入开始接收连接的名称：";
  cin.getline(charBuffer.data(), charBuffer.size());
  string cmdStr = charBuffer.data();
  cout << endl;
  // 接收客户端请求
  sockaddr_in clntAddr;
  uint32_t nSize = sizeof(sockaddr);
  int32_t clntSock = accept(serverSocket,(sockaddr*) &clntAddr, &nSize);
  clientMap[cmdStr] = clntSock;
}

void GLSocketServer::receiveFromClient() {
  cout << "请输入要接收消息的客户端名称：" ;
  cin.getline(charBuffer.data(), charBuffer.size());
  string clientName = charBuffer.data();
  int32_t &client = clientMap[clientName];
  int32_t recvSize =
      recv(client, charBuffer.data(), charBuffer.size() * sizeof(char), 0);
  string resultStr = charBuffer.data();
  cout << "接收到消息：" << endl;
  cout << resultStr << endl;
}

void GLSocketServer::printAllClientNames() {
  std::unordered_map<std::string, int32_t>::iterator it = clientMap.begin();
  for (uint32_t index = 0;;) {
    if (it == clientMap.end()) {
      std::cout << std::endl;
      break;
    }
    std::cout << "client" << index++ << ":" << it->first;
    it++;
  }
}
void GLSocketServer::sendStr2Client() {
  cout << "请输入要发送的客户端名称：";
  cin.getline(charBuffer.data(), 1024);
  string clientName = charBuffer.data();
  cout << "请输入要发送的字符内容：";
  cin.getline(charBuffer.data(), 1024);
  string msg = charBuffer.data();
  if (!clientMap.contains(clientName))
    throw std::runtime_error("client do not exist");
  int32_t &client = clientMap[clientName];

  int32_t sendMsgSize= send(client, msg.c_str(), msg.size() * sizeof(char), 0);
  
  assert(sendMsgSize > 0 && "发送消息失败");
  cout << "成功发送消息:" << msg<<endl;;
}

void GLSocketServer::initWindowsWSA() {
#ifdef WindowsVersion
  int32_t res= WSAStartup(MAKEWORD(2, 2), &wsaData);
  std::cout << "wsastartRes:" << res << std::endl;
#endif
}
void GLSocketServer::freeWindowsWSA(){
#ifdef WindowsVersion
  // 终止 DLL 的使用
  WSACleanup();
  #endif
}

void GLSocketServer::freeClients(){
    for(auto &pr:clientMap){
      #ifdef WindowsVersion
    closesocket(pr.second);
    #endif
    #ifdef LinuxVersion
    close(pr.second);
    #endif
    }
}

}  // namespace mystd