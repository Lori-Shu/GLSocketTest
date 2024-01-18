#include"MyTestAnnotation.h"
#include<iostream>
using namespace std;
int main(){
  Person p;
  GglClass* cls=p.getClass();
  cout<<"class name"<<cls->getClassName()<<endl;
  cout << "variable name" << cls->getVariables()[0].getVariableName()<<endl;
  cout << "variable typeName" << cls->getVariables()[0].getVariableTypeName()<<endl;
}