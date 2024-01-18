#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include<cassert>

class VariableDetail {
private:
  std::string variableTypeName;
  std::string variableName;
  size_t variableOffset;

public:
  VariableDetail(std::string tName, std::string vName, size_t offset) {
    variableTypeName = tName;
    variableName = vName;
    variableOffset = offset;
  }
  std::string getVariableName(){
    return variableName;
  }
  std::string getVariableTypeName() { return variableTypeName; }
};
class MethodArg {
private:
  std::string argTypeName;
  std::string argName;

public:
  MethodArg(std::string tName, std::string aName) {
    argTypeName = tName;
    argName = aName;
  }
};
class MethodDetail {
private:
  std::vector<MethodArg> methodArgs;
  std::string methodName;
  std::string returnTypeName;
  void *methodMemoryAddress;

public:
  MethodDetail(std::vector<MethodArg> args, std::string mName,
               std::string rtName, void *address) {
    methodArgs = args;
    methodName = mName;
    returnTypeName = rtName;
    methodMemoryAddress = address;
  }
};

class GglClass;
class GglClassManager {
private:
  std::unordered_map<std::string, GglClass *> gglClassMap;

public:
  GglClassManager() {}
  void insertClass(std::string s, GglClass *c) {
    gglClassMap.insert(std::pair(s, c));
  }
  GglClass *getGglClass(std::string s) {
    if (gglClassMap.find(s) == gglClassMap.end()) {
      std::cerr << "class does not exist" << std::endl;
      return nullptr;
    }
    return gglClassMap.at(s);
  }
  ~GglClassManager() {
    for (std::pair<std::string, GglClass *> p : gglClassMap) {
      delete p.second;
    }
  }
};
std::unique_ptr<GglClassManager> pClsManager =
    std::make_unique<GglClassManager>();
class GglClass {
private:
  bool finished;
  std::vector<VariableDetail> variables;
  std::vector<MethodDetail> methods;
  std::string className;

public:
  GglClass() { finished = false; }
  bool getFinished() { return finished; }
  void setFinished(bool b) { finished = b; }
  void checkAndFinish() {
    if (className.length() > 0) {

      setFinished(true);
      // gglClassMap.insert(className,this);
      pClsManager->insertClass(className, this);
    } else {
      std::cerr << "class config did not finish" << std::endl;
      exit(1);
    }
  }
  void addClassVariable(std::string variableTypeName, std::string variableName,
                        size_t offset) {
    variables.push_back(VariableDetail(variableTypeName, variableName, offset));
  }
  void addClassMethod(std::vector<MethodArg> args, std::string mName,
                      std::string rtName, void *address) {
    methods.push_back(MethodDetail(args, mName, rtName, address));
  }
  std::vector<VariableDetail> &getVariables() { return variables; }
  std::vector<MethodDetail> &getMethods() { return methods; }
  void setClassName(std::string s) { className = s; }
  std::string getClassName() { return className; }
};
class MethodExecutor {
public:
  MethodExecutor(void (*me)()) { me(); }
};
GglClass *cls;
#define GglClassHead()                                                         \
  void initClass() {                                                           \
    cls = new GglClass();                                                      \
  }                                                                            \
  MethodExecutor exeInit(initClass);
#define SetClassName(s)                                                        \
  void setClassNameMacro() { cls->setClassName(s); }                           \
  MethodExecutor exeSetName(setClassNameMacro);
#define AddClassVar(tName, vName, offset)                                      \
  void addClassVarMacro() { cls->addClassVariable(tName, vName, offset); }     \
  MethodExecutor exeAddVar(addClassVarMacro);
#define AddClassMethod(args, mName, rtName, address)                           \
  void addClassMethodMacro() {                                                 \
    cls->addClassMethod(args, mName, rtName, address);                         \
  }                                                                            \
  MethodExecutor exeAddMethod(addClassMethodMacro);
#define GglClassFoot()                                                         \
  void GglClassFootMacro() { cls->checkAndFinish(); }                          \
  MethodExecutor exeFoot(GglClassFootMacro);
