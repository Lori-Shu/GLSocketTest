#include <iostream>
#include<chrono>
#include "GLSocketServer.hpp"
#include"GGLThreadPool.h"
#include"GGLSelectMultiIO.h"
#include"GGLEpoll.h"
using namespace std;
void printNums(int32_t max,int32_t min) {
  for (int32_t num = min; num < max;) {
    // cout << "threadId:" << this_thread::get_id();
    cout << num << endl;
    ++num;
  }

}
int main() {
  cout << "----------------"
       << "welcome to GLServer"
       << "-------------------" << endl;
  // cout << "请输入serverPort:";
  // array<char, 7> portInput;
  // cin.getline(portInput.data(), 7);
  // cout << endl;
  // mystd::GLSocketServer sr{portInput.data()};
  // sr. loopCmd();
  // mystd::GGLThreadPool myThreadPool(5);
  // int32_t numMax = 50;
  // int32_t nums = 20;
  // for (int32_t index=0;index<20;){
  //   myThreadPool.submit(printNums, numMax,nums);
  //   ++index;
  // }
  // mystd::GGLSelectMultiIO mtio{};
  mystd::GGLEpoll epio{};
  
  cout << "hello" << endl;
  system("pause");
  return 0;
}

