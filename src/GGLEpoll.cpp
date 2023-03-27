#include"GGLEpoll.h"

namespace mystd{
using namespace std;
GGLEpoll::GGLEpoll(){
    createServerSocket();
    runEpollMainLoop();
}
GGLEpoll::~GGLEpoll(){

    closeSockets();
}


void GGLEpoll::createServerSocket(){
    sockaddr_in serverSockAddr{
      sin_family : PF_INET,
      sin_port : htons(PORT)

    };
    serverSockAddr.sin_addr.s_addr = inet_addr(serverAddrStr);
    serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    int32_t res =
        bind(serverSocket, (sockaddr *)&serverSockAddr, sizeof(serverSockAddr));
    cout << "bind res:" << res << endl;
    int32_t resListen = listen(serverSocket, 200);
    cout << "listen res:" << resListen << endl;
}
void GGLEpoll::runEpollMainLoop() {
    sockaddr_in clientAddr{};
    int32_t clientSocket;
    int32_t handleEventSize = 0, tempFD = serverSocket;
    uint32_t newSockLen;
    epollFd= epoll_create(bufSize);
    epoll_event temp,ep[bufSize];
    temp.data.fd=serverSocket;
    temp.events=EPOLLIN;
    int32_t addRes= epoll_ctl(epollFd,EPOLL_CTL_ADD,serverSocket,&temp);
    if(addRes!=0){
      cout<<"add serverSocket failed"<<endl;
    }
    for (;;) {
      handleEventSize =epoll_wait(epollFd,ep,bufSize,100);

      if (handleEventSize == -1) {
        cout << "epoll wait error" << endl;
      }
      for (; handleEventSize > 0;) {
        if(ep[handleEventSize-1].data.fd==serverSocket){
          clientSocket= accept(serverSocket,(sockaddr*)&clientAddr,&newSockLen);
          temp.data.fd = clientSocket;
          temp.events = EPOLLIN;

          addRes =
              epoll_ctl(epollFd, EPOLL_CTL_ADD, clientSocket, &temp);
          if (addRes != 0) {
            cout << "add socket failed" << addRes<<endl;
          }
          --handleEventSize;
          continue;
        }
        handleMsg(epollFd, ep[handleEventSize - 1]);
        --handleEventSize;
      }
    }
}
void GGLEpoll::handleMsg(int32_t epFd,epoll_event & event){
    int32_t clientFd=event.data.fd;
    int32_t resLen = recv(clientFd, msgBuffer.data(), msgBuffer.size(), 0);
    cout << "接收到信息长度:" << resLen << endl;
    if (resLen == 0 || resLen == -1) {
     int32_t delRes=  epoll_ctl(epFd,EPOLL_CTL_DEL,clientFd,&event);
     if (delRes != 0) {
        cout << "del socket failed" << endl;
     }
#ifdef WindowsVersion
      int32_t resCs = closesocket(socketFD);
#endif
#ifdef LinuxVersion
      int32_t resCs = close(clientFd);
#endif
      cout << "服务器关闭客户端文件描述符:" << clientFd << "res:" << resCs
           << endl;
      return;
    }
    int32_t index=0;
    for(;index<resLen;){
      msgBuffer[index] -= 32;
      ++ index;
    }
    int32_t sendSize= send(clientFd,msgBuffer.data(),resLen,0);
    if(sendSize==-1){
      cout<<"发送回客户端失败！"<<endl;
    }
}
void GGLEpoll:: closeSockets(){
  close(serverSocket);
  close(epollFd);
}
}
