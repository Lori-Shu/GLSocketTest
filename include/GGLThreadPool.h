#pragma once
#include<cstdint>
#include<mutex>
#include<condition_variable>
#include<vector>
#include<thread>
#include<functional>
#include<queue>
#include<chrono>
#include<unordered_set>
#include<iostream>
#define WindowsVersion
#ifdef WindowsVersion
#include<windows.h>
#endif
#ifdef LinuxVersion
#include<unistd.h>
#endif
namespace mystd{
using TaskFunc = std::function<void()>;
template<typename... T>
using AnyFuncPtr = void(*)(T...);
template <typename... T>
using TempFunc = std::function<void(T...)>;
class GGLThreadPool final{
 public:
  class GGLThread final{
   public:
    GGLThread(void (*task)(GGLThreadPool::GGLThread *,
                           GGLThreadPool *),
              GGLThreadPool* poolPtr);
    ~GGLThread();
    std::thread* tdPtr;
    GGLThreadPool* threadPool;
    bool shutDownFlag = false;
  };
  GGLThreadPool();
  ~GGLThreadPool();
  template <typename...T>
  void submit(AnyFuncPtr<T...> funcPtr, T &... t);
  int32_t getThreadPoolSize();
// private:
  void getHarderWareThreadConfig();

  void createSizeManager();
 
  void createThreads(int32_t size);
  template <typename T>
  TaskFunc bindFunctionToTaskFunc(TempFunc<T> func, T &t);
  template <typename R, typename... T,typename... Args>
  TaskFunc bindFunctionToTaskFunc(TempFunc<Args...> func, R &temp, T &...t);
  int32_t coreSize=0;
  int32_t maxThreadSize=0;
  GGLThread* sizeManager; 
  std::vector<GGLThread*> threads;
  const int32_t GGLTaskSize = 20;
  const int32_t defaultMinSize=2;
  std::unordered_set<GGLThread*> busyThreads;
  std::queue<TaskFunc> taskQueue;
  std::mutex threadsMtx;
  std::mutex queueMtx;
  std::mutex busyThreadsMtx;
  std::condition_variable produConVa;
  std::condition_variable consuConVa;
};
template <typename... T>
void GGLThreadPool::submit(AnyFuncPtr<T...> funcPtr, T &...t) {
  std::unique_lock<std::mutex> queueLock(queueMtx, std::defer_lock);
  queueLock.lock();
  for (; taskQueue.size() == GGLTaskSize;) {
    consuConVa.notify_one();
    produConVa.wait(queueLock);
  }
  TempFunc<T...> tf = funcPtr;
  TaskFunc fc = bind(tf, t...);
  taskQueue.push(fc);
  queueLock.unlock();
  consuConVa.notify_one();
}
// 递归获取...中的每个参数
template <typename T>
TaskFunc GGLThreadPool::bindFunctionToTaskFunc(TempFunc<T> func, T &t) {
  return bind(func, t);
}
template <typename R, typename... T,typename ...Args>
TaskFunc GGLThreadPool::bindFunctionToTaskFunc(TempFunc<Args...> func, R &temp, T &...t) {
  TempFunc<T...> tf = bind(func, temp);
  TaskFunc res = bindFunctionToTaskFunc(tf, t...);
  return res;
}
void mainTask(GGLThreadPool::GGLThread * tdPtr,GGLThreadPool * poolPtr);
void managePoolSize(GGLThreadPool::GGLThread * tdPtr,
                    GGLThreadPool * poolPtr);
}