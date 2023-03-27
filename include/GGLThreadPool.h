#pragma once
#include<cstdint>
#include<mutex>
#include<condition_variable>
#include<vector>
#include<thread>
#include<functional>
#include<queue>
namespace mystd{
using TaskFunc = std::function<void()>;
class GGLThreadPool  final{
  

 public:
  GGLThreadPool(int32_t size);
  ~GGLThreadPool();
  template <typename Func,typename...T>
  void submit(Func func, T &... t);

 private:
  void mainTask();
  void createThreads(int32_t size);
  template <typename Func, typename T>
  TaskFunc bindFunctionToTaskFunc(Func func, T &t);
  template <typename Func, typename R,typename... T>
  TaskFunc bindFunctionToTaskFunc(Func func,R &temp, T &...t);
  std::vector<std::thread> threads;
  const int32_t GGLTaskSize = 20;
  std::queue<TaskFunc> taskQueue;
  std::mutex mtx;
  std::condition_variable produConVa;
  std::condition_variable consuConVa;
  bool shutDownFlag = false;
};
template <typename Func, typename... T>
void GGLThreadPool::submit(Func func, T &...t) {
  std::unique_lock<std::mutex> queueLock(mtx, std::defer_lock);
  queueLock.lock();
  for (; taskQueue.size() == GGLTaskSize;) {
    consuConVa.notify_one();
    produConVa.wait(queueLock);
  }

  TaskFunc fc = std::bind(func, t...);
  taskQueue.push(fc);
  queueLock.unlock();
  produConVa.notify_one();
}
template <typename Func, typename T>
TaskFunc GGLThreadPool::bindFunctionToTaskFunc(Func func, T &t) {
  return bind(func, t);
}
template <typename Func, typename R, typename... T>
TaskFunc GGLThreadPool::bindFunctionToTaskFunc(Func func, R &temp, T &...t) {
  auto tf = bind(func, temp);
  auto res = bindFunctionToTaskFunc(tf, t...);
  return static_cast<TaskFunc>(res);
}
}