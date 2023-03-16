#include"GLSocketClient.hpp"
#include<iostream>
#include<vector>
#include<array>
using namespace std;
int main(){
  cout << "----------------"
       << "welcome to GLClient"
       << "-------------------" << endl;
  mystd::GLSocketClient glc;
  glc.loopCmd();
  system("pause");
  return 0;
}