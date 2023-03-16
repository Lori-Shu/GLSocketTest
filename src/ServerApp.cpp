#include <iostream>

#include "GLSocketServer.hpp"
using namespace std;
int main() {
  cout << "----------------"
       << "welcome to GLServer"
       << "-------------------" << endl;
  cout << "请输入serverPort:";
  array<char, 7> portInput;
  cin.getline(portInput.data(), 7);
  cout << endl;
  mystd::GLSocketServer sr{portInput.data()};
  sr. loopCmd();
  system("pause");
  return 0;
}