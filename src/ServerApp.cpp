#include <iostream>
#include<chrono>
#include "GLSocketServer.hpp"
#include"GGLThreadPool.h"
using namespace std;
void printNums(int32_t max) {
  for (int32_t num = 0; num < max;) {
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
  mystd::GGLThreadPool<int32_t> myThreadPool(5);
  int32_t numMax = 50;
  for (int32_t index=0;index<200;){
     myThreadPool.submit(printNums, numMax);
     ++index;
  }
  cout << "hello" << endl;
  system("pause");
  return 0;
}

