#pragma once
#include<string>
#include<iostream>
#include"GglClassAnnotation.h"
GglClassHead()
class Person{
private:
std::string personName;
public:
Person(){

}
void printName() { std::cout << "person name:" << personName << std::endl; }
GglClass* getClass(){
  return pClsManager->getGglClass("Person");
}
};
SetClassName("Person")
AddClassVar("string","personName",1)
AddClassMethod(std::vector<MethodArg>(),"printName","void",(void*)&Person::printName)
GglClassFoot()