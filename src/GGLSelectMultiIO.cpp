#include"GGLSelectMultiIO.h"
#include<vector>
#include <unordered_map>
#include<queue>
#include<unordered_set>

namespace mystd{
using namespace std;
GGLSelectMultiIO::GGLSelectMultiIO() {
  initWindowsWSA();
  createServerSocket();
     }
     GGLSelectMultiIO ::~GGLSelectMultiIO() {
  closeSockets();
  freeWindowsWSA(); 
        }

     void GGLSelectMultiIO:: createServerSocket(){
        SOCKADDR_IN serverSockAddr{
            sin_family:PF_INET,
             sin_port : htons(PORT)
            
        };
        serverSockAddr.sin_addr.s_addr = inet_addr("192.168.1.104");
        serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        int32_t res= bind(serverSocket, (SOCKADDR *)&serverSockAddr, sizeof(serverSockAddr));
        cout << "bind res:" << res << endl;
        int32_t resListen= listen(serverSocket, 20);
        cout << "listen res:" << resListen << endl;
        runSelectMainLoop();
      }
     void GGLSelectMultiIO::initWindowsWSA() {
  int32_t res = WSAStartup(MAKEWORD(2, 2), &wsaData);
  std::cout << "wsastartRes:" << res << std::endl;
   
}
void GGLSelectMultiIO::freeWindowsWSA() {
  // 终止 DLL 的使用
  int32_t res= WSACleanup();
  cout << "WSACleanup res:" << res << endl;
}
void GGLSelectMultiIO::runSelectMainLoop(){
  SOCKADDR_IN clientAddr{};
  SOCKET clientSocket{};
  maxFd = serverSocket;
  int32_t selectedSize=0,tempFD=serverSocket,socketLen=0;
  
  FD_ZERO(&readSet);
  FD_ZERO(&writeSet);
  FD_ZERO(&exceptionSet);
  FD_ZERO(&allSet);
  FD_SET(serverSocket, &allSet);
  for (;;){
    readSet=allSet;
    selectedSize= select(maxFd + 1, &readSet, &writeSet, &exceptionSet, nullptr);
    if(selectedSize==-1){
        cout<<"select error"<<endl;
    }
    if(FD_ISSET(serverSocket,&readSet)){
      clientSocket= accept(serverSocket, (SOCKADDR *)&clientAddr,&socketLen);
      
      maxFd=max<SOCKET>(clientSocket,maxFd);
      FD_SET(clientSocket, &allSet);
      --selectedSize;
    }
    tempFD = maxFd;
    for (;selectedSize>0;) {
        if(FD_ISSET(tempFD,&readSet)){
           handleMsg(tempFD);
           
          --selectedSize;
        }
        --tempFD;
  }
}
}
void GGLSelectMultiIO::handleMsg(SOCKET socketFD) {
 int32_t resLen= recv(socketFD, msgBuffer.data(), msgBuffer.size(), 0);
 cout << "接收到信息长度:" << resLen << endl;
 if(resLen==0||resLen==-1){
    FD_CLR(socketFD,&allSet);
    int32_t resCs= closesocket(socketFD);
    cout<<"服务器关闭客户端文件描述符:"<<socketFD<<"res:"<<resCs<<endl;
    return;
 }
 int32_t index = 0;
 for (;index<resLen;){
    msgBuffer[index]-=32;
    cout << msgBuffer[index]<<",";
    ++ index;
 } 
 cout<<endl;
 int32_t sendRes= send(socketFD,msgBuffer.data(),resLen,0);
 cout<<"send res:"<<sendRes<<endl;
 }
 void GGLSelectMultiIO::closeSockets() {
    for(;maxFd>serverSocket-1;){
        int32_t closeRes= closesocket(maxFd);
        cout<<"close res:"<<closeRes<<endl;
        --maxFd;
    }
 }
}